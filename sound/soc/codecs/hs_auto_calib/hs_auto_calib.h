#ifndef __HS_AUTO_CALIB_H__
#define __HS_AUTO_CALIB_H__
enum adjust_State{
	DEFAULT = 0,
	REC_JUDGE = DEFAULT,
	ERROR_JUDGE,
	VOL_INTERZONE_READJUST,
	//do_nothing,
	BTN_REPORT,
	BTN_RECORD,
	UNEXCEPTION_HANDLE
};

typedef enum vol_interzone_type {
	HOOK = 0,
	FORWARD,
	BACK,
	DEFAULT_TYPE,
	KEY_TYPE_MAX = DEFAULT_TYPE
} KEY_TYPE_ENUM;

struct calib_btn_voltage {/*mV*/
	unsigned short key_up_min_value;
	unsigned short key_up_max_value;
	unsigned short key_play_min_value;
	unsigned short key_play_max_value;
	unsigned short key_forward_min_value;
	unsigned short key_forward_max_value;
	unsigned short key_back_min_value;
	unsigned short key_back_max_value;
	unsigned short key_3_pole_min_voltage;
	unsigned short key_3_pole_max_voltage;
	unsigned short key_4_pole_min_voltage;
	unsigned short key_4_pole_max_voltage;
};

extern void headset_auto_calib_init(struct device_node *np);

extern void headset_auto_calib_reset_interzone();

extern void startup_FSM(enum adjust_State state, int hkadc_value, int * pr_btn_type);

#define BTN_HKADC_ERROR  25

/* Debug info */
#define ERROR_LEVEL     1
#define INFO_LEVEL      1
#define DEBUG_LEVEL     0

#if INFO_LEVEL
#define logi(fmt, ...) pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logi(fmt, ...)
#endif

#if DEBUG_LEVEL
#define logd(fmt, ...) pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logd(fmt, ...)
#endif

#if ERROR_LEVEL
#define loge(fmt, ...) pr_err(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define loge(fmt, ...)
#endif

#endif

