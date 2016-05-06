#ifndef __BSP_PINCTRL_H__
#define __BSP_PINCTRL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <product_config.h>
#include <bsp_gpio.h>

enum
{
    MODEM_PIN_INIT = 0,
    MODEM_PIN_NORMAL,
    MODEM_PIN_POWERDOWN,
    MODEM_PIN_BUTT,
};

/* wait for delete */
enum
{
    MODEM_IO_MUX = 0,
    MODEM_IO_CFG,
    MODEM_GPIO_INPUT,
    MODEM_GPIO_OUTPUT,
    MODEM_IO_BUTT,
};

struct pinctrl{
	unsigned int gpio;
	unsigned int iomg_off;
	unsigned int iomg_val;
	unsigned int iocg_off;
	unsigned int iocg_val;
	unsigned int gpio_dir;
	unsigned int gpio_val;
	unsigned int reserve;
};



#ifdef CONFIG_MODEM_PINTRL
void modem_pinctrl_init(void);
void modem_pintrl_config(int mode);

struct pinctrl * bsp_pinctrl_get(unsigned int mode, unsigned int gpio);
void bsp_pinctrl_put(const struct pinctrl *pctl);

int bsp_pinctrl_conf_set(const struct pinctrl *pctl, unsigned int conf);
int bsp_pinctrl_mux_set(const struct pinctrl *pctl, unsigned int mux);
int bsp_pinctrl_mux_get(const struct pinctrl *pctl);

int bsp_pinctrl_mux_modify (struct pinctrl *pctl, unsigned int mux);
int bsp_pinctrl_conf_modify(struct pinctrl *pctl, unsigned int conf);
int bsp_pinctrl_gpio_modify(struct pinctrl *pctl, unsigned int dir, unsigned int val);

#else
static inline void modem_pinctrl_init(void)
{
    return ;
}

static inline void modem_pintrl_config(int mode)
{
    return ;
}

static inline struct pinctrl * bsp_pinctrl_get(unsigned int mode, unsigned int gpio)
{
	static struct pinctrl dummy_pinctrl;
	return &dummy_pinctrl;
}

static inline void bsp_pinctrl_put(const struct pinctrl *pctl)
{
	return;
}


static inline int bsp_pinctrl_conf_set(const struct pinctrl *pctl, unsigned int conf)
{
    return 0;
}

static inline int bsp_pinctrl_mux_set(const struct pinctrl *pctl, unsigned int mux)
{
    return 0;
}

static inline int bsp_pinctrl_mux_get(const struct pinctrl *pctl)
{
    return 0;
}


static inline int bsp_pinctrl_mux_modify(struct pinctrl *pctl, unsigned int mux)
{
    return 0;
}

static inline int bsp_pinctrl_conf_modify(struct pinctrl *pctl, unsigned int conf)
{
    return 0;
}

static inline int bsp_pinctrl_gpio_modify(struct pinctrl *pctl, unsigned int dir, unsigned int val)
{
    return 0;
}

#endif

/*---------------------------wait for delete----------------------------------------*/
static inline int bsp_pinctrl_mux_set_stub(unsigned int gpio,unsigned int type)
{
    return 0;
}

static inline int bsp_pinctrl_mux_get_stub(unsigned int gpio)
{
    return 0;
}

static inline void bsp_pinctrl_modify_dts(unsigned int step ,unsigned int type, unsigned int gpio, unsigned int val)
{
    return ;
}

static inline void bsp_set_pintrl(unsigned int type, unsigned int gpio, unsigned int val)
{
    return ;
}
/*-----------------------------------------------------------------------------------------*/

static inline int bsp_pinctrl_set(const struct pinctrl *pctl, unsigned int mux, unsigned int conf, unsigned int dir, unsigned int val)
{
	if(dir)	{
		bsp_gpio_direction_output(pctl->gpio, val);
	}
	else {
		bsp_gpio_direction_input(pctl->gpio);
	}
	
    if(bsp_pinctrl_conf_set(pctl, conf)) {
		return -1;
	}
	
    if(bsp_pinctrl_mux_set(pctl, mux)) {
		return -1;
	}

    return 0;
}

static inline int bsp_pinctrl_modify(struct pinctrl *pctl, unsigned int mux, unsigned int conf, unsigned int dir, unsigned int val)
{
    if(bsp_pinctrl_gpio_modify(pctl, dir, val)) {
		return -1;
	}
	
    if(bsp_pinctrl_conf_modify(pctl, conf)) {
		return -1;
	}
	
    if(bsp_pinctrl_mux_modify(pctl, mux)) {
		return -1;
	}

    return 0;
}

static inline int bsp_pinctrl_modify_and_set(struct pinctrl *pctl, unsigned int mux, unsigned int conf, unsigned int dir, unsigned int val)
{
    if(bsp_pinctrl_set(pctl, mux, conf, dir, val)) {
		return -1;
	}
	
    if(bsp_pinctrl_modify(pctl, mux, conf, dir, val)) {
		return -1;
	}
    return 0;
}


#ifdef __cplusplus
}
#endif

#endif

