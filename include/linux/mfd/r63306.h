
#ifndef	__R63306_H
#define	__R63306_H

struct r63306_chip {
	struct device	*dev;
	struct mutex	*lock;
};

struct r63306_pwm {
	int	divider;
	int	duty_cycle;
	int	pwm_wm;
};

struct r63306_device_id {
	int	vendor;
	int	product;
	int	revision;
};

struct r63306_cabc {
	bool	cabc_on;
	bool	pwm_on;
	bool	pfm_on;
	bool	ledpwm_pin;
	bool	ledpwm_pol;
};

struct r63306_cabc_param {
	int	backlight;
};

extern int dsi_reset(void);
extern int dsi_enter_sleep(void);
extern int dsi_exit_sleep(void);
extern int dsi_get_pwm(struct r63306_pwm *pwm);
extern int dsi_set_pwm(struct r63306_pwm *pwm);
extern int dsi_get_cabc(struct r63306_cabc *cabc);
extern int dsi_set_cabc(struct r63306_cabc *cabc);
extern int dsi_get_cabc_param(struct r63306_cabc_param *cabc);
extern int dsi_set_cabc_param(struct r63306_cabc_param *cabc);
extern int dsi_get_backlight(int *level);

#endif	/* __R63306_H */
