#ifndef __RF_ANTEN_CFG_H__
#define __RF_ANTEN_CFG_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif            /* __cplusplus */

#include <product_config.h>
#include <osl_sem.h>
#include <drv_nv_def.h>

#define  ANTEN_TASK_STACK_SIZE  (0x1000) 
#define  ANTEN_TASK_PRIORITY    (VX_DEFAULT_PRIORITY - 1)

#define  OUTER_RFSWITCH_ON   1
#define  OUTER_RFSWITCH_OFF  0

typedef struct {
    u32 caller_addr;
    u32 para1;
    u32 para2;
    u32 para3;
    u32 timestamp;
    int ret;
}FEMIO_CALLINFO_S;

typedef void (*ANTEN_FUNCPTR)(void);

struct anten_msg_stru
{
    unsigned int modem_id;
    unsigned int status;
};

typedef struct{
    struct anten_msg_stru msg;
    osl_sem_id            sem_id;
    ANTEN_FUNCPTR         routine[PWC_COMM_MODEM_BUTT];
}ANTEN_DETECT_INFO;

typedef enum{
    GPIO_FUNCTION =0,
    ANT_FUNCTION,
    ANT_FUNC_BUTT,
}ANT_PIN_FUNC;

#ifdef CONFIG_RFFE_ANTEN
/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_poweron(u32 modem_id);

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem关机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_poweroff(u32 modem_id);

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : 两个modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
int balong_rf_config_anten_allpoweroff( void );

int balong_rf_config_anten_init(void);

/*****************************************************************************
* 函 数    : balong_rf_anten_resume
* 功 能    : 天线相关低功耗唤醒
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_anten_resume(void);

/*****************************************************************************
* 函 数    : balong_rf_anten_suspend
* 功 能    : 天线相关低功耗睡眠配置
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int balong_rf_anten_suspend(void);

#else
/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static inline int balong_rf_config_anten_poweron(u32 modem_id)
{
    return RFFE_OK;
}
/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : modem关机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static inline int balong_rf_config_anten_poweroff(u32 modem_id)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rf_config_anten_pin_function
* 功 能    : 两个modem开机时射频管脚配置
* 输 入    : @pin 射频管脚编号

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static inline int balong_rf_config_anten_allpoweroff( void )
{
    return RFFE_OK;
}

static inline int balong_rf_config_anten_init(void)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rf_anten_resume
* 功 能    : 天线相关低功耗唤醒
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static inline int balong_rf_anten_resume(void)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rf_anten_suspend
* 功 能    : 天线相关低功耗睡眠配置
* 输 入    : 无

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static inline int balong_rf_anten_suspend(void)
{
    return RFFE_OK;
}
#endif

#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */

