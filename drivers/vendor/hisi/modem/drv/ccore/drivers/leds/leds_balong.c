
#include <osl_types.h>
#include <mdrv_public.h>
#include <mdrv_leds.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_leds.h>
#include <bsp_om.h>
#include <bsp_softtimer.h>
#include <bsp_nvim.h>

struct softtimer_list led_softtimer ; 
unsigned char g_cur_work_state = LED_LIGHT_STATE_MAX; /* 保存上层工作状态 */
unsigned char g_new_work_state = LED_LIGHT_STATE_MAX; /* 初始化的工作状态与g_cur_work_state保持一致 */
pFUNCPTR p_func_tled_state_get = NULL;              /* new BSP_TLED_LedFlush, 用于挂载上层注册的回调函数，获取上层工作状态 */
unsigned int led_debug_level;                       /* for LED_TRACE level */

/*******************************************************************************
 * FUNC NAME:
 * led_default_callback() 
 * Function     : C核软timer默认回调函数
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 新的工作状态
 * Decription   : 在上层注册回调函数之前，作为默认的回调函数
 ************************************************************************/
unsigned char led_default_callback(void)
{
    return g_new_work_state;
}

/*******************************************************************************
 * FUNC NAME:
 * led_state_check_callback() - C核软timer回调函数
 * Function     : 
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : null
 * Decription   : 
 ************************************************************************/
void led_state_check_callback(void)
{
    int ret = LED_ERROR;

    /* 获取上层状态 */
    if (NULL != p_func_tled_state_get)
    {
        g_new_work_state = (unsigned char)((*p_func_tled_state_get)());
    }
    else
    {
        return; 
    }
    
    LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]LED get new state success, new state %d\n", __FUNCTION__, g_new_work_state);
    
    /* 与当前状态进行比较，若不同，则更新当前状态并通知A核闪灯 */
    if(g_cur_work_state != g_new_work_state)
    {
        ret = bsp_icc_send(ICC_CPU_APP, LED_ICC_CHN_ID, (unsigned char*)&g_new_work_state, sizeof(unsigned char)); 
        if(ret != (int)sizeof(unsigned char))
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR), "[%s]icc send failed, new state %d, length %d\n", 
                __FUNCTION__, g_new_work_state, ret);
            return;
        }

        LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]icc send success, new state %d\n", __FUNCTION__, g_new_work_state);
        
        g_cur_work_state = g_new_work_state;
    }
    
    LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]LED same state, skip\n", __FUNCTION__);

    bsp_softtimer_add(&led_softtimer);

    return;
}

/*******************************************************************************
 * FUNC NAME:
 * led_softtimer_create() 
 * Function     : 创建软timer
 * Arguments
 *      input   : @timer - timer的定时时间
 *                @wake_type - timer对CPU的唤醒类型
 *      output  : null
 *
 * Return       : LED_OK - 成功；else - 失败
 * Decription   : null
 ************************************************************************/
int led_softtimer_create(unsigned int time, enum wakeup wake_type)
{
    led_softtimer.func = (softtimer_func)led_state_check_callback;
    led_softtimer.para = 0;                              
    led_softtimer.timeout = time;                        /* 定时长度，单位ms */
    led_softtimer.wake_type = wake_type;

    if (bsp_softtimer_create(&led_softtimer))
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s]ERROR: softtimer create failed\n", __FUNCTION__);
        return LED_ERROR;
    }
    
    bsp_softtimer_add(&led_softtimer);

    LED_TRACE(LED_DEBUG_LEVEL(INFO), "LED create softtimer OK\n");
    
    return LED_OK;
}

/*******************************************************************************
 * FUNC NAME:
 * bsp_led_init() 
 * Function     : c核led初始化函数
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : LED_OK - 成功；else - 失败
 * Decription   : 
 ************************************************************************/
int bsp_led_init(void)
{
    DRV_MODULE_TEST_STRU ctrl;
    int ret = LED_ERROR;

    ret = (s32)bsp_nvm_read(NV_ID_DRV_TEST_SUPPORT, (u8 *)&ctrl, sizeof(DRV_MODULE_TEST_STRU));
    if(ret){
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"error: read nv failed, ret = %d, enable default\n", ret);
        ctrl.leds = 1;
    }

    if(0 == ctrl.leds)
        return LED_OK;

    /* 初始化上层工作状态 */
    g_cur_work_state = LED_LIGHT_STATE_MAX;

    p_func_tled_state_get = (pFUNCPTR)led_default_callback;

    /* 创建软timer(不唤醒)，注册回调函数 */
    ret = led_softtimer_create(LED_TIME_BASE_UNIT, SOFTTIMER_NOWAKE);
    if(ret != LED_OK)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] softtimer create failed, ret = 0x%x\n", __FUNCTION__, ret);
        return ret;
    }   

    LED_TRACE(LED_DEBUG_LEVEL(ALWAYS), "LED init OK\n");

    return ret;
}

/*******************************************************************************
 * FUNC NAME:
 * led_set_debug_level() 
 * Function     : open all debug level
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 
 * Decription   : 
 ************************************************************************/
void led_set_debug_level(void)
{
    led_debug_level = LED_DEBUG_ALL;
}

/*****************************************************************************
 函 数 名  : drv_led_flash
 功能描述  : 三色灯设置。
 输入参数  : status：三色灯的状态
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
int drv_led_flash(unsigned long state)
{
    g_new_work_state = (unsigned char)state;
    return 0;
}

/****************************************************************************
 函 数 名  : drv_led_state_func_reg
 功能描述  : 本接口为提供给协议栈的钩子函数，用于获取协议栈的点灯状态。
 输入参数  : 协议栈获取点灯状态函数的指针。
 输出参数  : 无。
 返 回 值  : 无。
 注意事项  : 无。

******************************************************************************/
void drv_led_state_func_reg (pFUNCPTR p)
{
    p_func_tled_state_get = p;
}
