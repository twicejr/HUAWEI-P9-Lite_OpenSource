#ifndef __HUAWEI_TOUCHSCREEN_ALGO_H_
#define __HUAWEI_TOUCHSCREEN_ALGO_H_
#include "huawei_touchscreen_chips.h"


#define TP_FINGER 				1
#define TP_STYLUS				2
#define TP_GLOVE 				6
#define FILTER_GLOVE_NUMBER	4

#define PEN_MOV_LENGTH      120  //move length (pixels)
#define FINGER_REL_TIME     300  //the time pen checked after finger released shouldn't less than this value(ms)

enum TP_state_machine {
	INIT_STATE = 0,
	ZERO_STATE = 1,		//switch finger to glove
	FINGER_STATE = 2,	//finger state
	GLOVE_STATE = 3	//glove state
};

int ts_register_algo_func(struct ts_device_data *chip_data);
#endif
