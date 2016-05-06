

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#ifdef _PRE_CONFIG_USE_DTS
#include <linux/of.h>
#include <linux/of_gpio.h>
#endif
/*lint -e322*//*lint -e7*/
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/pinctrl/consumer.h>
/*lint +e322*//*lint +e7*/

#include "board.h"
#include "plat_debug.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
BOARD_INFO g_board_info = {0};

/*****************************************************************************
  3 Function Definition
*****************************************************************************/
extern irqreturn_t bfg_wake_host_isr(int irq, void *dev_id);

inline BOARD_INFO * get_board_info(void)
{
	return &g_board_info;
}

#ifdef _PRE_CONFIG_USE_DTS
int32 get_board_dts_node(struct device_node ** np, const char * node_prop)
{
	if (NULL ==np || NULL == node_prop)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, node_prop=%p\n", np, node_prop);
		return BOARD_FAIL;
	}

	*np = of_find_compatible_node(NULL, NULL, node_prop);
	if (NULL == *np)
	{
		PS_PRINT_ERR("HISI IPC:No compatible node found.\n");
		return BOARD_FAIL;
	}

	return BOARD_SUCC;
}

int32 get_board_dts_prop(struct device_node *np, const char * dts_prop, const char ** prop_val)
{
	int32 ret = BOARD_FAIL;

	if (NULL == np || NULL == dts_prop || NULL == prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, dts_prop=%p, prop_val=%p\n", np, dts_prop, prop_val);
		return BOARD_FAIL;
	}

	ret = of_property_read_string(np, dts_prop, prop_val);
    if (ret)
    {
        PS_PRINT_ERR("can't get dts_prop value: dts_prop=%s\n", dts_prop);
        return ret;
    }

	PS_PRINT_SUC("have get dts_prop and prop_val: %s=%s\n", dts_prop, *prop_val);

	return BOARD_SUCC;
}

int32 get_board_dts_gpio_prop(struct device_node *np, const char * dts_prop, int32 * prop_val)
{
	int32 ret = BOARD_FAIL;

	if (NULL == np || NULL == dts_prop || NULL == prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, dts_prop=%p, prop_val=%p\n", np, dts_prop, prop_val);
		return BOARD_FAIL;
	}

    ret = of_get_named_gpio(np, dts_prop, 0);
    if (ret < 0)
    {
        PS_PRINT_ERR("can't get dts_prop value: dts_prop=%s, ret=%d\n", dts_prop, ret);
        return ret;
    }

    *prop_val = ret;
	PS_PRINT_SUC("have get dts_prop and prop_val: %s=%d\n", dts_prop, *prop_val);

	return BOARD_SUCC;
}

#endif

int32 get_board_gpio(const char * gpio_node, const char * gpio_prop, int32 *physical_gpio)
{
#ifdef _PRE_CONFIG_USE_DTS
	int32 ret= BOARD_FAIL;
	struct device_node * np = NULL;

	ret = get_board_dts_node(&np, gpio_node);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = get_board_dts_gpio_prop(np, gpio_prop, physical_gpio);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	return BOARD_SUCC;
#else
	return BOARD_SUCC;
#endif
}

int32 get_board_custmize(const char * cust_node, const char * cust_prop, const char **cust_prop_val)
{
#ifdef _PRE_CONFIG_USE_DTS
	int32 ret= BOARD_FAIL;
	struct device_node * np = NULL;

	if (NULL == cust_node || NULL == cust_prop || NULL == cust_prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!\n");
		return BOARD_FAIL;
	}

	ret = get_board_dts_node(&np, cust_node);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = get_board_dts_prop(np, cust_prop, cust_prop_val);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	PS_PRINT_INFO("get board customize info %s=%s\n", cust_prop, *cust_prop_val);

	return BOARD_SUCC;
#else
	return BOARD_SUCC;
#endif
}

int32 get_board_pmu_clk32k(void)
{
	int32 ret= BOARD_FAIL;
	const char * clk_name = NULL;

	PS_PRINT_DBG("in func\n");
	ret = get_board_custmize(DTS_NODE_HI110X, DTS_PROP_CLK_32K, &clk_name);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	g_board_info.clk_32k_name = clk_name;

	return BOARD_SUCC;
}

int32 set_board_pmu_clk32k(struct platform_device *pdev)
{
	int32 ret= BOARD_FAIL;
	const char * clk_name = NULL;
	struct clk* clk = NULL;
	struct device *dev = NULL;

	PS_PRINT_DBG("in func\n");
	dev = &pdev->dev;
	clk_name = g_board_info.clk_32k_name;
	clk = devm_clk_get(dev, "clk_pmu32kb");
    if (NULL == clk)
	{
        PS_PRINT_ERR("Get 32k clk %s failed!!!\n", clk_name);
        return BOARD_FAIL;
	}
	g_board_info.clk_32k = clk;

	ret = clk_prepare_enable(clk);
    if (unlikely(ret < 0))
    {
		devm_clk_put(dev, clk);
        PS_PRINT_ERR("enable 32K clk failed!!!");
        return BOARD_FAIL;
    }

	return BOARD_SUCC;
}

int32 get_board_uart_port(void)
{
	int32 ret= BOARD_FAIL;
	const char *uart_port = NULL;

	PS_PRINT_INFO("in func\n");

	ret = get_board_custmize(DTS_NODE_HI110X_BFGX, DTS_PROP_UART_POART, &uart_port);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}
	g_board_info.uart_port = uart_port;

	return BOARD_SUCC;
}

int32 check_evb_or_fpga(void)
{
#ifdef _PRE_CONFIG_USE_DTS
    int32 ret= BOARD_FAIL;
    struct device_node * np = NULL;

    ret = get_board_dts_node(&np, DTS_NODE_HI110X);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X);
        return BOARD_FAIL;
    }

    ret = of_property_read_bool(np, DTS_PROP_VERSION);
    if (ret)
    {
        PS_PRINT_INFO("HI1102 ASIC VERSION\n");
        g_board_info.is_asic = VERSION_ASIC;
    }
    else
    {
        PS_PRINT_INFO("HI1102 FPGA VERSION\n");
        g_board_info.is_asic = VERSION_FPGA;
    }

    return BOARD_SUCC;
#else
    return BOARD_SUCC;
#endif
}

int32 board_get_power_pinctrl(struct platform_device *pdev)
{
    int32  ret = BOARD_FAIL;
    int32  physical_gpio = 0;
    struct device_node * np = NULL;
    struct pinctrl *pinctrl;
    struct pinctrl_state *pinctrl_def;
    struct pinctrl_state *pinctrl_idle;

    /* 检查是否需要prepare before board power on */
    /* JTAG SELECT 拉低，XLDO MODE选择2.8v */
	ret = get_board_dts_node(&np, DTS_NODE_HI110X);
	if(BOARD_SUCC != ret)
	{
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X);
        goto err_read_dts_node;
	}

    ret = of_property_read_bool(np, DTS_PROP_POWER_PREPARE);
    if (ret)
    {
        PS_PRINT_INFO("need prepare before board power on\n");
        g_board_info.need_power_prepare = NEED_POWER_PREPARE;
    }
    else
    {
        PS_PRINT_INFO("no need prepare before board power on\n");
        g_board_info.need_power_prepare = NO_NEED_POWER_PREPARE;
    }

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return BOARD_SUCC;
    }

    pinctrl = devm_pinctrl_get(&pdev->dev);
    if (IS_ERR_OR_NULL(pinctrl))
    {
        PS_PRINT_ERR("iomux_lookup_block failed, and the value of pinctrl is %p\n", pinctrl);
        goto err_pinctrl_get;
    }
    g_board_info.pctrl = pinctrl;

    pinctrl_def = pinctrl_lookup_state(pinctrl, "default");
    if (IS_ERR_OR_NULL(pinctrl_def))
    {
        PS_PRINT_ERR("pinctrl_lookup_state default failed, and the value of pinctrl_def is %p\n", pinctrl_def);
        goto err_lookup_default;
    }
    g_board_info.pins_normal = pinctrl_def;

    pinctrl_idle = pinctrl_lookup_state(pinctrl, "idle");
    if (IS_ERR_OR_NULL(pinctrl_idle))
    {
        PS_PRINT_ERR("pinctrl_lookup_state idel failed, and the value of pinctrl_idle is %p\n", pinctrl_idle);
        goto err_lookup_idle;
    }
    g_board_info.pins_idle = pinctrl_idle;

    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_normal);
    if (ret < 0)
    {
        PS_PRINT_ERR("pinctrl_select_state default failed.\n");
        goto err_select_state;
    }

    /* LTE_TX_ACTIVT GPIO */
    ret = get_board_gpio(DTS_NODE_HI110X, DTS_PROP_GPIO_XLDO_PINMUX, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_POWEN_ON);
        goto err_get_xldo_pinmux;
    }

    g_board_info.xldo_pinmux = physical_gpio;

    ret = of_property_read_u32(np, DTS_PROP_GPIO_XLDO_LEVEL, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_XLDO_LEVEL);
        goto err_read_xldo_level;
    }

    g_board_info.gpio_xldo_level = physical_gpio;

    return BOARD_SUCC;

    err_read_xldo_level:
    err_get_xldo_pinmux:
    err_select_state:
    err_lookup_idle:
    err_lookup_default:
        devm_pinctrl_put(g_board_info.pctrl);
    err_pinctrl_get:
    err_read_dts_node:

    return BOARD_FAIL;
}

int32 board_gpio_init(void)
{
    int32 ret= BOARD_FAIL;
    int32 physical_gpio = 0;

    PS_PRINT_INFO("in func\n");

    /*power on gpio request*/
    ret = get_board_gpio(DTS_NODE_HI110X, DTS_PROP_GPIO_POWEN_ON, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
	    PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_POWEN_ON);
        goto err_get_power_on_gpio;
    }

    g_board_info.power_on_enable = physical_gpio;

    ret = gpio_request_one(physical_gpio, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_POWEN_ON);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_POWEN_ON);
        goto err_get_power_on_gpio;
    }

    /*wifi wake host gpio request*/
    ret = get_board_gpio(DTS_NODE_HI110X_WIFI, DTS_PROP_GPIO_WLAN_WAKEUP_HOST, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
	    PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_WLAN_WAKEUP_HOST);
        goto err_get_wlan_wkup_host_gpio;
    }

    g_board_info.wlan_wakeup_host = physical_gpio;

    ret = gpio_request_one(physical_gpio, GPIOF_IN, PROC_NAME_GPIO_WLAN_WAKEUP_HOST);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_WLAN_WAKEUP_HOST);
        goto err_get_wlan_wkup_host_gpio;
    }

    /*bfgx wake host gpio request*/
	ret = get_board_gpio(DTS_NODE_HI110X_BFGX, DTS_PROP_GPIO_BFGN_WAKEUP_HOST, &physical_gpio);
	if(BOARD_SUCC != ret)
	{
	    PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_BFGN_WAKEUP_HOST);
		goto err_get_bfgx_wkup_host_gpio;
	}

	g_board_info.bfgn_wakeup_host = physical_gpio;

	ret = gpio_request_one(physical_gpio, GPIOF_IN, PROC_NAME_GPIO_BFGN_WAKEUP_HOST);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_BFGN_WAKEUP_HOST);
        goto err_get_bfgx_wkup_host_gpio;
    }

    /* ir ctrl gpio request */
    ret = get_board_gpio(DTS_NODE_HI110X_BFGX, DTS_PROP_GPIO_BFGN_IR_CTRL, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_INFO("dts prop %s not exist\n", DTS_PROP_GPIO_BFGN_IR_CTRL);
        g_board_info.bfgn_ir_ctrl= -1;
    }
    else
    {
        g_board_info.bfgn_ir_ctrl= physical_gpio;

        ret = gpio_request_one(physical_gpio, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_BFGN_IR_CTRL);
        if (ret)
        {
            PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_BFGN_IR_CTRL);
            goto err_get_ir_ctrl_gpio;
        }
    }

    return BOARD_SUCC;

    err_get_ir_ctrl_gpio:
        gpio_free(g_board_info.bfgn_wakeup_host);
    err_get_bfgx_wkup_host_gpio:
        gpio_free(g_board_info.wlan_wakeup_host);
    err_get_wlan_wkup_host_gpio:
        gpio_free(g_board_info.power_on_enable);
    err_get_power_on_gpio:

    return BOARD_FAIL;
}

int board_get_bwkup_gpio_val(void)
{
    return gpio_get_value(g_board_info.bfgn_wakeup_host);
}

int board_get_wlan_wkup_gpio_val(void)
{
    return gpio_get_value(g_board_info.wlan_wakeup_host);
}


int32 board_irq_init(void)
{
	int32 ret = BOARD_FAIL;
	uint32 irq = 0;
	int32 gpio = 0;

	PS_PRINT_INFO("in func\n");

	gpio = g_board_info.wlan_wakeup_host;
	irq = gpio_to_irq(gpio);
	g_board_info.wlan_irq = irq;

	PS_PRINT_INFO("wlan_irq is %d\n", g_board_info.wlan_irq);

	gpio = g_board_info.bfgn_wakeup_host;
	irq = gpio_to_irq(gpio);

	ret = request_irq(irq, bfg_wake_host_isr, IRQF_DISABLED | IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND, "bfgx_wake_host", NULL);
    if (ret < 0)
    {
        PS_PRINT_ERR("couldn't acquire %s IRQ\n", PROC_NAME_GPIO_BFGN_WAKEUP_HOST);
		return BOARD_FAIL;
    }
	g_board_info.bfgn_irq = irq;

	PS_PRINT_INFO("bfgx_irq is %d\n", g_board_info.bfgn_irq);

	return BOARD_SUCC;
}

int32 board_clk_init(struct platform_device *pdev)
{
	int32 ret= BOARD_FAIL;

	PS_PRINT_INFO("in func\n");

	if (NULL == pdev)
	{
        PS_PRINT_ERR("func has NULL input param!!!\n");
		return BOARD_FAIL;
	}

	ret = get_board_pmu_clk32k();
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = set_board_pmu_clk32k(pdev);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	return BOARD_SUCC;
}

void prepare_to_power_on(void)
{
    int32 ret = BOARD_FAIL;

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return;
    }

    if (IS_ERR_OR_NULL(g_board_info.pctrl) || IS_ERR_OR_NULL(g_board_info.pins_idle))
    {
        PS_PRINT_ERR("power pinctrl is err, pctrl is %p, pins_idle is %p\n", g_board_info.pctrl, g_board_info.pins_idle);
        return;
    }

    /* set LowerPower mode */
    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_idle);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("power prepare:set LOWPOWER mode failed, ret:%d\n", ret);
        return;
    }

    ret = gpio_request_one(g_board_info.xldo_pinmux, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_XLDO_PINMUX);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_XLDO_PINMUX);
        return;
    }

    gpio_direction_output(g_board_info.xldo_pinmux, g_board_info.gpio_xldo_level);
    g_board_info.pinmux_set_result = PINMUX_SET_SUCC;

    return;
}

void post_to_power_on(void)
{
    int32 ret = BOARD_FAIL;

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return;
    }

    if (PINMUX_SET_SUCC == g_board_info.pinmux_set_result)
    {
        g_board_info.pinmux_set_result = PINMUX_SET_INIT;
        gpio_free(g_board_info.xldo_pinmux);
    }

    if (IS_ERR_OR_NULL(g_board_info.pctrl) || IS_ERR_OR_NULL(g_board_info.pins_normal))
    {
        PS_PRINT_ERR("power pinctrl is err, pctrl is %p, pins_idle is %p\n", g_board_info.pctrl, g_board_info.pins_normal);
        return;
    }

    /* set NORMAL mode */
    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_normal);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("power prepare:set NORMAL mode failed, ret:%d\n", ret);
        return;
    }

    return;
}

void board_power_on(void)
{
    prepare_to_power_on();

    gpio_direction_output(g_board_info.power_on_enable, GPIO_LOWLEVEL);
    mdelay(10);
    gpio_direction_output(g_board_info.power_on_enable, GPIO_HIGHLEVEL);
    mdelay(30);

    post_to_power_on();
}

void board_power_off(void)
{
    gpio_direction_output(g_board_info.power_on_enable, GPIO_LOWLEVEL);
}

STATIC int32 hi110x_board_probe(struct platform_device *pdev)
{
	int ret = BOARD_FAIL;
	PS_PRINT_INFO("enter\n");

    ret = board_clk_init(pdev);
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

	ret = get_board_uart_port();
	if (BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = board_gpio_init();
	if (BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = check_evb_or_fpga();
	if (BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = board_irq_init();
	if (BOARD_SUCC != ret)
	{
		goto err_gpio_source;
	}

    ret = board_get_power_pinctrl(pdev);
    if (BOARD_SUCC != ret)
    {
        goto err_get_power_pinctrl;
    }

	PS_PRINT_INFO("board init ok\n");

    return BOARD_SUCC;

    err_get_power_pinctrl:
        free_irq(g_board_info.bfgn_irq, NULL);
	err_gpio_source:
        if (g_board_info.bfgn_ir_ctrl > -1)
        {
            gpio_free(g_board_info.bfgn_ir_ctrl);
        }
        gpio_free(g_board_info.bfgn_wakeup_host);
        gpio_free(g_board_info.wlan_wakeup_host);
        gpio_free(g_board_info.power_on_enable);

    return BOARD_FAIL;
}

STATIC int32 hi110x_board_remove(struct platform_device *pdev)
{
	PS_PRINT_INFO("enter\n");

    if (NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        devm_pinctrl_put(g_board_info.pctrl);
    }

    free_irq(g_board_info.bfgn_irq, NULL);

    if (g_board_info.bfgn_ir_ctrl > -1)
    {
        gpio_free(g_board_info.bfgn_ir_ctrl);
    }

    gpio_free(g_board_info.bfgn_wakeup_host);
    gpio_free(g_board_info.wlan_wakeup_host);
    gpio_free(g_board_info.power_on_enable);

    return BOARD_SUCC;
}

int32 hi110x_board_suspend(struct platform_device *pdev, pm_message_t state)
{
    return BOARD_SUCC;
}

int32 hi110x_board_resume(struct platform_device *pdev)
{
    return BOARD_SUCC;
}

#ifdef _PRE_CONFIG_USE_DTS
static struct of_device_id hi110x_board_match_table[] = {
	{
		.compatible = DTS_COMP_HI110X_BOARD_NAME,
		.data = NULL,
    },
	{ },
};
#endif

STATIC struct platform_driver hi110x_board_driver = {
        .probe      = hi110x_board_probe,
        .remove     = hi110x_board_remove,
        .suspend    = hi110x_board_suspend,
        .resume     = hi110x_board_resume,
        .driver     = {
            .name   = "hi110x_board",
            .owner  = THIS_MODULE,
#ifdef _PRE_CONFIG_USE_DTS
			.of_match_table	= hi110x_board_match_table,
#endif
        },
};

int32 hi110x_board_init(void)
{
    int32 ret = BOARD_FAIL;

    PS_PRINT_FUNCTION_NAME;

    ret = platform_driver_register(&hi110x_board_driver);
    if (ret)
    {
        PS_PRINT_ERR("Unable to register hisi connectivity board driver.\n");
    }

    return ret;
}

void hi110x_board_exit(void)
{
    platform_driver_unregister(&hi110x_board_driver);
}


