/*
 * via_gpios.h
 *
 */
#ifndef VIA_GPIOS_H
#define VIA_GPIOS_H

#include <linux/wait.h>
#include <linux/types.h>


#define MAX_GPIO_NAME_LENGTH    64
/* enumeration of via gpio type */
typedef enum via_gpio_type
{
    GPIO_APCP_DATA_ACK,
    GPIO_APCP_FLOW_CTRL,
    GPIO_4WIRE_AP_WK_CP,
    GPIO_4WIRE_CP_READY,
    GPIO_4WIRE_CP_WK_AP,
    GPIO_4WIRE_AP_READY,
    GPIO_APCP_SPI_RTS,    /* only used in SPI bus read */
    GPIO_APCP_BUS_RESET, /* used to reset SPI bus or SDIO bus */
    GPIO_NR,
} via_gpio_type_e;

enum gpio_level_active_type
{
    GPIO_LEVEL_ACTIVE_LOW,
    GPIO_LEVEL_ACTIVE_HIGH,
    GPIO_LEVEL_ACTIVE_SWITCH,
};

enum gpio_level_type
{
    GPIO_LEVEL_LOW,
    GPIO_LEVEL_HIGH,
};

typedef enum
{
    GPIO_STATE_INACTIVE,
    GPIO_STATE_ACTIVE, /* gpio is ready */
    GPIO_STATE_UNKNOW
} gpio_state_e;

typedef struct gpio_attribute
{
    const char m_gpio_name[MAX_GPIO_NAME_LENGTH];
    int m_gpio_num;        /* gpio number */
    int m_gpio_polar;    /* gpio active polar */
    int m_need_irq;
    unsigned int m_irq_type;
    int m_need_wait;
    wait_queue_head_t m_wait_q;
    atomic_t m_state_atom;
} gpio_attribute_t;

typedef struct via_gpios_mgmt
{
    atomic_t m_rst_ind_finished;

    gpio_attribute_t m_arr_via_gpios[GPIO_NR];

} via_gpios_mgmt_t;


int get_apcp_gpio_level(via_gpio_type_e t_gpio_type);
void set_apcp_gpio_output_level(via_gpio_type_e t_gpio_type, int level);
void reset_apcp_gpio_state(via_gpio_type_e t_gpio_type);
int wait_apcp_gpio_state(via_gpio_type_e t_gpio_type);


#endif
