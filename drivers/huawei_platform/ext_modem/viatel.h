#ifndef VIATEL_H
#define VIATEL_H

#include <linux/interrupt.h>
#include <huawei_platform/log/hw_log.h>
#include "core.h"

#define GPIO_OEM_UNKNOW (-1)
#define GPIO_OEM_VALID(gpio) ((gpio <= GPIO_OEM_UNKNOW) ? 0 : 1)

#undef HWLOG_TAG
#define HWLOG_TAG viacbp82d_3rd_modem
HWLOG_REGIST();
//HWLOG_REGIST_LEVEL(HWLOG_ERR|HWLOG_WARNING | HWLOG_INFO|HWLOG_DEBUG|HWLOG_DEBUG1|HWLOG_DEBUG2|HWLOG_DEBUG3|HWLOG_DEBUG4);

#define FIFO_SIZE	8*PAGE_SIZE //need page aligned

//////////////////////////////////////////////////////////////////////////////////
/*******************************  Gpio Config ***********************************/
//////////////////////////////////////////////////////////////////////////////////

#ifdef GPIO_VIA_CBP_BCKUP_1
#define GPIO_VIATEL_CRASH_CBP GPIO_VIA_CBP_BCKUP_1
#else
#define GPIO_VIATEL_CRASH_CBP GPIO_OEM_UNKNOW
#endif


//////////////////////////////////////////////////////////////////////////////////
/****************************** Gpio Function   *********************************/
//////////////////////////////////////////////////////////////////////////////////
int oem_gpio_request(int gpio, const char* label);
void oem_gpio_free(int gpio);
/*config the gpio to be input for irq if the SOC need*/
int oem_gpio_direction_input_for_irq(int gpio);
int oem_gpio_direction_output(int gpio, int value);
int oem_gpio_get_value(int gpio);
int oem_gpio_get_value_cansleep(int gpio);
int oem_gpio_to_irq(int gpio);
int oem_irq_to_gpio(int irq);
int oem_gpio_set_irq_type(int gpio, unsigned int type);
int oem_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags, const char* name, void* dev);
int oem_gpio_request_threaded_irq(int gpio, irq_handler_t handler, unsigned long flags, const char* name, void* dev);
void oem_gpio_irq_mask(int gpio);
void oem_gpio_irq_unmask(int gpio);

#define ASC_NAME_LEN   (64)
#define MDM_RESETINFO_SIZE  (1024)
#define CBP_EXCEPT_STACK_LEN (512)
/*used to register handle*/

struct cbp_reset_info_s {
    u8  task_name[ASC_NAME_LEN];
    u32 modid;
    u8  stack[CBP_EXCEPT_STACK_LEN];
};

#define CBP_EXCEPT_REASON_RILD "RILD"
#define CBP_EXCEPT_REASON_SPI "SPI"
#define CBP_EXCEPT_RILD_AT_TIMEOUT "2"
//////////////////////////////////////////////////////////////////////////////////
/*******************************  Power Control *********************************/
//////////////////////////////////////////////////////////////////////////////////
/* modem event notification values */
enum clock_event_nofitiers
{
    MDM_EVT_NOTIFY_POWER_ON = 0,
    MDM_EVT_NOTIFY_POWER_OFF,
    MDM_EVT_NOTIFY_RESET_ON,
    MDM_EVT_NOTIFY_RESET_OFF,
    MDM_EVT_NOTIFY_HD_ERR,
    MDM_EVT_NOTIFY_HD_ENHANCE,
    MDM_EVT_NOTIFY_NUM
};

enum cbp_except_type_e {
    CBP_EXCE_TYPE_RILD = 0,
    CBP_EXCE_TYPE_SPI,
    CBP_EXCE_TYPE_NUM
};

enum cbp_except_modid_e{
    CBP_EXCE_MID_RILD_AT_TIMEOUT = 0x0100,

    CBP_EXCE_MID_SPI_READ_TIMEOUT = 0x0200,
    CBP_EXCE_MID_SPI_WRITE_TIMEOUT,
    CBP_EXCE_MID_SPI_SFLOW_TIMEOUT,
    CBP_EXCE_MID_SPI_CFLAG80_PKT_TIMEOUT,
    CBP_EXCE_MID_SPI_ETS_SFLOW_RESET,
};
void modem_notify_event(int event);
int modem_register_notifier(struct notifier_block* nb);
int modem_unregister_notifier(struct notifier_block* nb);
#endif
