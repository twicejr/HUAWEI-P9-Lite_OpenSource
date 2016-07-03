#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include<linux/slab.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <sound/jack.h>
#include <linux/of_gpio.h>
#include "hs_auto_calib.h"

#define LOG_TAG "hs_auto_calib"

#define OF_KEY_VALUE_GET(np, name, value, def_val)  \
do {\
	ret = of_property_read_u32(np, name, value); \
	if(ret != 0) { \
		*value = def_val; \
		logi("name is %d",*value); \
	} \
} while(0)

#define DEFAULT_ERROR 35

static bool hs_auto_calib_enable = false;
static int g_vol_record[KEY_TYPE_MAX] = {-1};
static struct calib_btn_voltage btn_voltage = {0};
static int g_vol_error[KEY_TYPE_MAX] = {DEFAULT_ERROR, DEFAULT_ERROR, DEFAULT_ERROR};
static int g_vol_distance = DEFAULT_ERROR;
static int g_vol_btn = FORWARD;

enum auto_btn_voltage{/*mV*/
	KEY_HOOK_MIN_VALUE  = 0,
	KEY_HOOK_MAX_VALUE = 135,
	KEY_FORWARD_MIN_VALUE = 136,
	KEY_FORWARD_MAX_VALUE = 350,
	KEY_BACK_MIN_VALUE  = 351,
	KEY_BACK_MAX_VALUE = 700
};

/*
 * return true if g_vol_record is empty
 */
static bool  isVolRecordEmpty()
{
	int i = 0;
	for(i = FORWARD; i < g_vol_btn; i++) {
		if((g_vol_record[i] != -1) )
			return false;
	}
	return true;
}

void headset_auto_calib_init(struct device_node * np)
{
	struct device_node *ncp = NULL;
	/* ret is needed by OF_KEY_VALUE_GET */
	int ret = 0;
	char *status = NULL;
	logi("begin\n");
	/* re-config the keys */
	ncp = of_get_child_by_name(np, "hs_auto_calib");
	if (ncp == NULL) {
		goto err;
	}
	if(of_property_read_string(ncp, "status", &status)) {
		goto err;
	}
	if(!strcmp(status, "ok")) {
		hs_auto_calib_enable = true;
	} else {
		hs_auto_calib_enable = false;
		return;
	}

	OF_KEY_VALUE_GET(ncp, "key_play_min_value", &btn_voltage.key_play_min_value, KEY_HOOK_MIN_VALUE);
	OF_KEY_VALUE_GET(ncp, "key_play_max_value", &btn_voltage.key_play_max_value, KEY_HOOK_MAX_VALUE);
	OF_KEY_VALUE_GET(ncp, "key_forward_min_value", &btn_voltage.key_forward_min_value, KEY_FORWARD_MIN_VALUE);
	OF_KEY_VALUE_GET(ncp, "key_forward_max_value", &btn_voltage.key_forward_max_value, KEY_FORWARD_MAX_VALUE);
	OF_KEY_VALUE_GET(ncp, "key_back_min_value", &btn_voltage.key_back_min_value, KEY_BACK_MIN_VALUE);
	OF_KEY_VALUE_GET(ncp, "key_back_max_value", &btn_voltage.key_back_max_value, KEY_BACK_MAX_VALUE);
	logi("end\n");
	return;
err:
	hs_auto_calib_enable = false;
	return;
}

/* clear stored hkadc_value */
void headset_auto_calib_reset_interzone()
{
	//resume the initial interzone.
	int i = 0;
	logi("begin\n");
	for(i = FORWARD; i < KEY_TYPE_MAX; i++) {
		g_vol_record[i] = -1;
		g_vol_error[i] = DEFAULT_ERROR;
	}
	g_vol_btn = FORWARD;
	logi("end\n");
	return;
}

static KEY_TYPE_ENUM check_hs_type (int hkadc_value)
{
	KEY_TYPE_ENUM press_key = DEFAULT_TYPE;
	logi("begin, hkadc_value %d\n", hkadc_value);
	if ((hkadc_value >= btn_voltage.key_play_min_value)
			&& (hkadc_value <= btn_voltage.key_play_max_value)) {
		press_key = HOOK;
	} else if ((hkadc_value >= btn_voltage.key_forward_min_value)
			&& (hkadc_value <= btn_voltage.key_forward_max_value)) {
		press_key = FORWARD;
	} else if ((hkadc_value >= btn_voltage.key_back_min_value)
			&& (hkadc_value <= btn_voltage.key_back_max_value)) {
		press_key = BACK;
	} else {
		logi("hkadc value is not in range , hkadc value is %d", hkadc_value);
	}
	logi("end press_key %d", press_key);
	return press_key;
}

/* Des: set pressed key type.
 * Param: press_key key pressed.
 * 		  btn_type  key_type to store.
 */
static void set_hs_type(int * btn_type , int  press_key)
{
	logi("begin, btn_type %d\n", *btn_type);
	if (press_key != DEFAULT_TYPE) {
		*btn_type = (int)(SND_JACK_BTN_0 >> press_key);
	} else {
		*btn_type = 0;
	}
	logi("end ");
	return;
}

/*
 *modify g_vol_error g_vol_distance
 *
 */
static void store_error()
{
	int temp=0;
	int vol_distance = 0;
	logi("begin g_vol_error[FORWARD] %d g_vol_error[BACK] %d\n", g_vol_error[FORWARD], g_vol_error[BACK]);
	vol_distance = g_vol_record[BACK] - g_vol_record[FORWARD];
	g_vol_distance = (g_vol_distance > vol_distance) ? g_vol_distance : vol_distance;
	g_vol_error[BACK] = g_vol_distance >> 1;
	temp = (g_vol_record[FORWARD] - btn_voltage.key_play_max_value) >> 1;
	g_vol_error[FORWARD] = (g_vol_error[BACK] > temp) ? temp : g_vol_error[BACK];
	g_vol_error[BACK] = g_vol_distance - g_vol_error[FORWARD];
	logi("end g_vol_error[FORWARD] %d g_vol_error[BACK] %d\n", g_vol_error[FORWARD], g_vol_error[BACK]);
}


/*
 *record vol ,modify g_vol_error g_vol_distance and g_vol_record_num and throw wrong value.
 */
static void record_sort(int hkadc_value)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	logi("hkadc_value %d \n", hkadc_value);
	if (hkadc_value < btn_voltage.key_play_max_value) {
		g_vol_record[HOOK] = hkadc_value;
		return;
	}
	switch (g_vol_btn) {
	case FORWARD:
		g_vol_record[FORWARD] = hkadc_value;
		g_vol_btn = BACK;
		break;

	case BACK:
		if (hkadc_value > g_vol_record[FORWARD]) {
			g_vol_record[BACK] = hkadc_value;
		} else {
			temp = g_vol_record[FORWARD];
			g_vol_record[FORWARD] = hkadc_value;
			g_vol_record[BACK] = temp;
		}
		g_vol_btn = KEY_TYPE_MAX;
		store_error();
		break;

	case KEY_TYPE_MAX:
		//discard error
		if(hkadc_value < g_vol_record[FORWARD]) {
			g_vol_record[FORWARD] = hkadc_value;
		} else if (hkadc_value > g_vol_record[BACK]) {
			g_vol_record[BACK] = hkadc_value;
		}
		store_error();
		break;

	default:
		break;
	}
	logi("end");

}

//normally, this function will be called when unpressed key has been pressed.
//Exceptionally, this function will be called when a button error is out of range.
static void readjust_interzone()
{
	logi("begin\n");
	btn_voltage.key_forward_max_value = (g_vol_record[FORWARD] +g_vol_record[BACK])/2;
	btn_voltage.key_back_min_value = btn_voltage.key_forward_max_value + 1;
	logi("interzone reset to key_forward_max=%d , key_back_min= %d\n",btn_voltage.key_forward_max_value,btn_voltage.key_back_min_value);
	logi("end\n");

}

/* g_vol_record compare with it's g_vol_error.
 * return false means the voltage not belonging to error range,
 * return true means the voltage is error.
 */
static bool is_voltage_error(int hkadc_value)
{
	int i = 0;
	logi("begin, hkadc_value %d\n", hkadc_value);
	//has this button being pressed
	for(i = (int )FORWARD; i < g_vol_btn; i++) {
		if(abs(hkadc_value - g_vol_record[i])  < g_vol_error[i]) {
			return true;
		}
	}

	logi("end\n");
	return false;
}

void startup_FSM(enum adjust_State state, int hkadc_value, int * pr_btn_type)
{
	if(!hs_auto_calib_enable)
	{
		return;
	}

	if(hkadc_value > btn_voltage.key_back_max_value)
	{
		loge("error:hkadc_value[%d] is bigger than max value!!!", hkadc_value);
		return;
	}

	logi("begin, adjust_state %d hkadc_value %d\n", state, hkadc_value);
	int headset_type = 0;
	while(1) {
		switch(state) {
		case REC_JUDGE:
			//if all record is empty goto report ,else ERROR_JUDGE
			if(isVolRecordEmpty()) {
				state = BTN_RECORD;
			} else {
				state = ERROR_JUDGE;
			}
			break;

		case ERROR_JUDGE:
			//avoid the hardware feedback error
			if (is_voltage_error(hkadc_value)) {
				state = BTN_REPORT;
			} else {
				state = BTN_RECORD;
			}
			break;

		case BTN_RECORD:
			/*
			 *record vol and modify g_vol_error g_vol_record.
			 */
			record_sort(hkadc_value);
			if(g_vol_btn == KEY_TYPE_MAX) {
				state = VOL_INTERZONE_READJUST;
			} else {
				state = BTN_REPORT;
			}
			break;

		case VOL_INTERZONE_READJUST:
			//interzone judge and re-adjust the threshold
			readjust_interzone();
			state = BTN_REPORT;
			break;

		case BTN_REPORT:
			headset_type = (int)check_hs_type(hkadc_value);
			set_hs_type((int *)pr_btn_type, headset_type);
			logi("hkadc_value %d BTN_REPORT %d\n",hkadc_value,headset_type);
			return;

		default:
			break;
		}
	}
}
