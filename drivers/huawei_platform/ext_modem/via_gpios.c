/*
 * apcp_gpios.c
 *
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

#include "viatel.h"
#include "via_spi.h"
#include "rnic_adapter.h"
#include "apcp_test.h"
#include "via_gpios.h"
#include "4wire_wake.h"
#include "ext_modem.h"
#include "via_sdio.h"
#include "modem_channels.h"
#include "modem_packet.h"
#include "modem_ttys.h"
#define VIA_APCP_GPIOS_DRIVER_NAME  "huawei,viacbp82d-cbp-spi"

#define WAIT_GPIO_TIMEOUT_ONCE_IN_MS    2000


/* global via gpios management variable */
static via_gpios_mgmt_t g_via_gpios =
{
    .m_rst_ind_finished = ATOMIC_INIT(0),
    /* every gpio attribute list as following format:     m_gpio_name,  m_gpio_num, m_gpio_polar, \
                                                                                m_need_irq, m_irq_type, \
                                                                                m_need_wait, m_wait_q, m_state_atom*/
    .m_arr_via_gpios[GPIO_APCP_DATA_ACK] =  {"via_data_ack",         -1, GPIO_LEVEL_ACTIVE_LOW, \
        1, IRQF_TRIGGER_FALLING, \
        1, 0, ATOMIC_INIT(0)
    },
    .m_arr_via_gpios[GPIO_APCP_FLOW_CTRL] = {"via_flow_ctrl",       -1, GPIO_LEVEL_ACTIVE_LOW,   \
        1, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, \
        1, 0, ATOMIC_INIT(0)
    },
    .m_arr_via_gpios[GPIO_4WIRE_AP_WK_CP] = {"via_ap_wkup_cp",      -1, GPIO_LEVEL_ACTIVE_LOW,    \
        0, 0, \
        0, 0, ATOMIC_INIT(0)
    },
    .m_arr_via_gpios[GPIO_4WIRE_CP_READY] = {"via_cp_ready",        -1, GPIO_LEVEL_ACTIVE_LOW,    \
        1, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, \
        1, 0, ATOMIC_INIT(0)
    },
    .m_arr_via_gpios[GPIO_4WIRE_CP_WK_AP] = {"via_cp_wkup_ap",      -1, GPIO_LEVEL_ACTIVE_LOW,    \
        1, IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, \
        0, 0, ATOMIC_INIT(0)
    },
    .m_arr_via_gpios[GPIO_4WIRE_AP_READY] = {"via_ap_ready",        -1, GPIO_LEVEL_ACTIVE_LOW,    \
        0, 0, \
        0, 0, ATOMIC_INIT(0)
    },
};


static irqreturn_t via_gpio_irq_handle(int irq, void* pt_data)
{
    int level;
    gpio_attribute_t* p_via_gpio_attr = (gpio_attribute_t*)pt_data;

    level = !!oem_gpio_get_value(p_via_gpio_attr->m_gpio_num);

    if (p_via_gpio_attr->m_need_wait)
    {
        if (level != p_via_gpio_attr->m_gpio_polar)
        {
            atomic_set(&(p_via_gpio_attr->m_state_atom), GPIO_STATE_INACTIVE);
        }
        else
        {
            atomic_set(&(p_via_gpio_attr->m_state_atom), GPIO_STATE_ACTIVE);
            wake_up(&(p_via_gpio_attr->m_wait_q));
        }
    }

    if (0 == get_modem_bus_state())
    {
        hwlog_info("%s %d: gpio %d irq level=%d\n", __func__, __LINE__, p_via_gpio_attr->m_gpio_num, level);
    }

    if (g_via_gpios.m_arr_via_gpios[GPIO_4WIRE_CP_WK_AP].m_gpio_num == p_via_gpio_attr->m_gpio_num)
    {
        /* call cp wake_ap isr from four wire driver */
        cp_wake_ap_isr(level);
    }
    else if (g_via_gpios.m_arr_via_gpios[GPIO_APCP_SPI_RTS].m_gpio_num == p_via_gpio_attr->m_gpio_num)
    {
        hwlog_debug("%s %d entered, m_rst_ind_finished = %d\n", __func__, __LINE__, atomic_read(&g_via_gpios.m_rst_ind_finished));

        if (GPIO_STATE_INACTIVE == atomic_read(&g_via_gpios.m_rst_ind_finished))
        {
            hwlog_err("unexpected rts interrupt before reset indication flag m_rst_ind_finished set.\n");
            return IRQ_HANDLED;
        }

        /* call via spi rts top-half irq handler from VIA SPI driver */
        via_spi_rts_isr();
    }

    oem_gpio_irq_unmask(p_via_gpio_attr->m_gpio_num);

    return IRQ_HANDLED;
}

/* for flow control gpio, GPIO_STATE_ACTIVE means flow control DISABLED, that is to say AP can send data to CP */
int wait_apcp_gpio_state(via_gpio_type_e t_gpio_type)
{
    unsigned long remain_time;
    int ret = 0;
    unsigned int old_gpio_value = 0;

    //hwlog_debug("%s %d Enter. gpio_type is %d.\n", __func__, __LINE__, t_gpio_type);
    old_gpio_value = oem_gpio_get_value(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_num);
    remain_time = wait_event_timeout(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_wait_q, \
                                     ((GPIO_STATE_ACTIVE == atomic_read(&(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_state_atom))) \
                                      || (0 == get_modem_bus_state())), msecs_to_jiffies(WAIT_GPIO_TIMEOUT_ONCE_IN_MS));

    if (0 == get_modem_bus_state())
    {
        hwlog_err("%s %d VIA CBP reset happened!.\n", __func__, __LINE__);
        ret = -2;
    }
    else if (0 == remain_time)
    {
        hwlog_err("%s %d wait gpio active timeout 2s. gpio=%d wait polar=%d, old value =%d,current value=%d", \
                  __func__, __LINE__, g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_num, g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_polar, \
                  old_gpio_value, oem_gpio_get_value(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_num));
        ret = -1;
    }

    return ret;
}
EXPORT_SYMBOL(wait_apcp_gpio_state);

/* for flow control gpio, GPIO_STATE_ACTIVE means flow control DISABLED, that is to say AP can send data to CP */
void reset_apcp_gpio_state(via_gpio_type_e t_gpio_type)
{
    /* just after check the gpio state, set gpio state to inactive as early as possible */
    atomic_set(&(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_state_atom), GPIO_STATE_INACTIVE);
}
EXPORT_SYMBOL(reset_apcp_gpio_state);

void set_apcp_gpio_output_level(via_gpio_type_e t_gpio_type, int t_level)
{
    /* check the gpio type */
    oem_gpio_direction_output(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_num, t_level);
}
EXPORT_SYMBOL(set_apcp_gpio_output_level);

int get_apcp_gpio_level(via_gpio_type_e t_gpio_type)
{
    int gpio_level;

    gpio_level = oem_gpio_get_value(g_via_gpios.m_arr_via_gpios[t_gpio_type].m_gpio_num);
    hwlog_debug("%s %d ap wake cp gpio level is %d.\n", __func__, __LINE__, gpio_level);

    return gpio_level;
}
EXPORT_SYMBOL(get_apcp_gpio_level);

void gpio_irq_cbp_rst_ind(int level)
{
    hwlog_info("%s %d enter.\n", __func__, __LINE__);
    atomic_set(&g_via_gpios.m_rst_ind_finished, GPIO_STATE_ACTIVE);

    if (level)   /*1:cbp reset happened*/
    {
        set_modem_bus_state(0);
        hwlog_info("%s %d set modem_power_state=%d.\n", __func__, __LINE__, get_modem_bus_state());
        wake_up(&g_via_gpios.m_arr_via_gpios[GPIO_APCP_DATA_ACK].m_wait_q);
        wake_up(&g_via_gpios.m_arr_via_gpios[GPIO_APCP_FLOW_CTRL].m_wait_q);
    }
    else
    {
        set_modem_bus_state(1);
        hwlog_info("%s %d set modem_power_state=%d.\n", __func__, __LINE__, get_modem_bus_state());
    }

    modem_reset_handle();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
EXPORT_SYMBOL(gpio_irq_cbp_rst_ind);

static int via_gpios_probe(struct platform_device* pt_pdev)
{
    int ret = -1;
    struct device* p_dev = &pt_pdev->dev;
    struct device_node* np = p_dev->of_node;
    int i = 0;

    hwlog_info("%s %d enter.\n", __func__, __LINE__);
    ret = platform_device_add_data(pt_pdev, &g_via_gpios, sizeof(via_gpios_mgmt_t));

    if (ret < 0)
    {
        hwlog_err("%s: add platform_data failed!\n", __func__);
        goto err_plat_add_data;
    }

    for (i = 0; i < GPIO_NR; i++)
    {
        g_via_gpios.m_arr_via_gpios[i].m_gpio_num = of_get_named_gpio(np, g_via_gpios.m_arr_via_gpios[i].m_gpio_name, 0);
        hwlog_info(">>>> %s get %s gpio %d\n", __func__, g_via_gpios.m_arr_via_gpios[i].m_gpio_name, g_via_gpios.m_arr_via_gpios[i].m_gpio_num);

        if (GPIO_OEM_VALID(g_via_gpios.m_arr_via_gpios[i].m_gpio_num))
        {
            /* 1. must first initialize wait_q, because gpio irq handle use it */
            if (g_via_gpios.m_arr_via_gpios[i].m_need_wait)
            {
                init_waitqueue_head(&(g_via_gpios.m_arr_via_gpios[i].m_wait_q));
                atomic_set(&(g_via_gpios.m_arr_via_gpios[i].m_state_atom), GPIO_STATE_ACTIVE);
            }

            /* 2. requset gpio */
            ret = oem_gpio_request(g_via_gpios.m_arr_via_gpios[i].m_gpio_num, g_via_gpios.m_arr_via_gpios[i].m_gpio_name);

            if (ret < 0)
            {
                hwlog_err("%s: %d fail to requset gpio %d ret =%d!!\n",
                          __func__, __LINE__, g_via_gpios.m_arr_via_gpios[i].m_gpio_num, ret);
                goto err_gpio_request;
            }

            /* 3. last request irq */
            if (g_via_gpios.m_arr_via_gpios[i].m_need_irq)
            {
                oem_gpio_irq_mask(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);
                oem_gpio_direction_input_for_irq(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);
                oem_gpio_set_irq_type(g_via_gpios.m_arr_via_gpios[i].m_gpio_num, g_via_gpios.m_arr_via_gpios[i].m_irq_type);
                ret = oem_gpio_request_irq(g_via_gpios.m_arr_via_gpios[i].m_gpio_num, via_gpio_irq_handle, \
                                           IRQF_SHARED | g_via_gpios.m_arr_via_gpios[i].m_irq_type, \
                                           g_via_gpios.m_arr_via_gpios[i].m_gpio_name, &(g_via_gpios.m_arr_via_gpios[i]));
                oem_gpio_irq_unmask(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);

                if (ret < 0)
                {
                    hwlog_err("%s: %d fail to request irq for %s!\n", __func__, __LINE__, g_via_gpios.m_arr_via_gpios[i].m_gpio_name);
                    goto err_request_irq;
                }
            }
        }
    }

    atomic_set(&g_via_gpios.m_rst_ind_finished, GPIO_STATE_INACTIVE);

    ret = ext_modem_init();

    if (ret)
    {
        hwlog_err("%s %d: ext_modem_init return error\n", __func__, __LINE__);
        goto err_ext_modem_init;
    }

    ret = via_spi_init();

    if (ret)
    {
        hwlog_err("%s %d: via_spi_init return error\n", __func__, __LINE__);
        goto err_via_spi_init;
    }

    ret = via_sdio_init();

    if (ret)
    {
        hwlog_err("%s %d: via_sdio_init return error\n", __func__, __LINE__);
        goto err_via_sdio_init;
    }

    ret = modem_channels_init();

    if (ret)
    {
        hwlog_err("%s %d: modem_channels_init return error\n", __func__, __LINE__);
        goto err_modem_channels_init;
    }

    ret = modem_packet_init();

    if (ret)
    {
        hwlog_err("%s %d: modem_ttys_init return error\n", __func__, __LINE__);
        goto err_modem_packet_init;
    }

    rnic_txrx_init();

    ret = four_wire_wake_init();

    if (ret)
    {
        hwlog_err("%s %d: four_wire_wake_init return error\n", __func__, __LINE__);
        goto err_4wire_wake_init;
    }

    ret = modem_ttys_init();

    if (ret)
    {
        hwlog_err("%s %d: modem_ttys_init return error\n", __func__, __LINE__);
        goto err_modem_ttys_init;
    }

    apcp_test_init();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;

err_modem_ttys_init:
    modem_ttys_exit();
err_4wire_wake_init:
err_modem_packet_init:
    modem_packet_exit();
err_modem_channels_init:
    modem_channels_exit();
err_via_sdio_init:
    via_sdio_exit();
err_via_spi_init:
    via_spi_exit();
err_ext_modem_init:
    ext_modem_exit();
err_request_irq:

    if (GPIO_OEM_VALID(g_via_gpios.m_arr_via_gpios[i].m_gpio_num))
    {
        oem_gpio_free(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);
    }

err_gpio_request:

    for (; i >= 0; i--)
    {
        if (GPIO_OEM_VALID(g_via_gpios.m_arr_via_gpios[i].m_gpio_num))
        {
            oem_gpio_free(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);

            if (g_via_gpios.m_arr_via_gpios[i].m_need_irq)
            {
                free_irq(oem_gpio_to_irq(g_via_gpios.m_arr_via_gpios[i].m_gpio_num), &(g_via_gpios.m_arr_via_gpios[i]));
            }
        }
    }

err_plat_add_data:
    return ret;
}

static int via_gpios_remove(struct platform_device* pt_pdev)
{
    int i = 0;

    hwlog_info("%s %d enter.\n", __func__, __LINE__);

    for (i = 0; i < GPIO_NR; i++)
    {
        if (GPIO_OEM_VALID(g_via_gpios.m_arr_via_gpios[i].m_gpio_num))
        {
            oem_gpio_free(g_via_gpios.m_arr_via_gpios[i].m_gpio_num);

            if (g_via_gpios.m_arr_via_gpios[i].m_need_irq)
            {
                free_irq(oem_gpio_to_irq(g_via_gpios.m_arr_via_gpios[i].m_gpio_num), &(g_via_gpios.m_arr_via_gpios[i]));
            }
        }
    }

    //rnic_adapter_exit();

    modem_ttys_exit();

    modem_channels_exit();

    via_sdio_exit();

    via_spi_exit();

    ext_modem_exit();

    modem_packet_exit();

    hwlog_info("%s %d exit.\n", __func__, __LINE__);
    return 0;
}

static const struct of_device_id via_gpios_match_table[] =
{
    {
        .compatible = VIA_APCP_GPIOS_DRIVER_NAME,
        .data = NULL,
    },
    {
    },
};
MODULE_DEVICE_TABLE(of, via_gpios_match_table);

static struct platform_driver via_gpios_plat_driver =
{
    .driver = {
        .name = "huawei,viacbp82d-cbp-spi",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(via_gpios_match_table),
    },
    .probe        = via_gpios_probe,
    .remove        = via_gpios_remove,
};

static int __init via_gpios_init(void)
{
    int ret;

    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    ret = platform_driver_register(&via_gpios_plat_driver);

    if (ret)
    {
        hwlog_err("platform_driver_register failed\n");
        return -1;
    }

    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;
}

late_initcall(via_gpios_init);

static void __exit via_gpios_exit(void)
{
    hwlog_info("%s %d: Enter.\n", __func__, __LINE__);
    platform_driver_unregister(&via_gpios_plat_driver);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}

module_exit(via_gpios_exit);

MODULE_DESCRIPTION("Via gpios driver");
