/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Dmac_PM.c
  版 本 号   : 初稿
  作    者   : Zourong
  生成日期   : 2013年6月18日
  最近修改   :
  功能描述   : 全局静态状态机二维函数表
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月18日
    作    者   : Zourong
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PM
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_pm.h"
#include "dmac_ap_pm.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AP_PM_C

OAL_STATIC oal_void ap_power_state_work_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_work_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_work_event(oal_void *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_deep_sleep_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_deep_sleep_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_deep_sleep_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_wow_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_wow_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_wow_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_idle_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_idle_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_idle_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);


OAL_STATIC oal_void ap_power_state_off_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_off_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_off_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_uint32 dmac_pm_ap_inactive_timer(oal_void* pst_arg);
OAL_STATIC oal_void dmac_pm_state_trans(mac_pm_handler_stru* pst_handler,oal_uint8 uc_state);

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 全局状态机函数表 */
mac_fsm_state_info  g_ap_power_fsm_info[] = {
    {
          PWR_SAVE_STATE_WORK,
          "WORK",
          ap_power_state_work_entry,
          ap_power_state_work_exit,
          ap_power_state_work_event,
    },
    {
          PWR_SAVE_STATE_DEEP_SLEEP,
          "DEEP_SLEEP",
          ap_power_state_deep_sleep_entry,
          ap_power_state_deep_sleep_exit,
          ap_power_state_deep_sleep_event,
    },
    {
          PWR_SAVE_STATE_WOW,
          "WOW",
          ap_power_state_wow_entry,
          ap_power_state_wow_exit,
          ap_power_state_wow_event,
    },
    {
          PWR_SAVE_STATE_IDLE,
          "IDLE",
          ap_power_state_idle_entry,
          ap_power_state_idle_exit,
          ap_power_state_idle_event,
    },
    {
          PWR_SAVE_STATE_OFF,
          "OFF",
          ap_power_state_off_entry,
          ap_power_state_off_exit,
          ap_power_state_off_event,
    }
};

/*VAP状态到device状态的映射表*/
oal_uint8 g_pm_state_map[PWR_SAVE_STATE_BUTT] =
{
    DEV_PWR_STATE_WORK,          //->PWR_SAVE_STATE_WORK = 0,         /*工作状态*/
    DEV_PWR_STATE_DEEP_SLEEP,    //->PWR_SAVE_STATE_DEEP_SLEEP,      /*深睡状态*/
    DEV_PWR_STATE_WOW,           //->PWR_SAVE_STATE_WOW,             /*WOW状态*/
    DEV_PWR_STATE_IDLE,         //->PWR_SAVE_STATE_IDLE,            /*idle状态，无用户关联*/
    DEV_PWR_STATE_OFF            //->PWR_SAVE_STATE_OFF,
};

#define DMAC_VAP2DEV_PM_STATE(_uc_state) (g_pm_state_map[_uc_state])

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : ap_power_state_work_entry
 功能描述  : work状态的entry接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_work_entry(oal_void *p_ctx)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;
    oal_uint32              ul_core_id;

    ul_core_id = OAL_GET_CORE_ID();
    //dmac_vap_stru *pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);


    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return ;
    }

    pst_pm_handler->ul_user_check_count = 0;
    pst_pm_handler->ul_inactive_time    = 0;
    if((pst_pm_handler->bit_pwr_siso_en)||(pst_pm_handler->bit_pwr_wow_en))
    {
        if (OAL_FALSE == pst_pm_handler->st_inactive_timer.en_is_registerd)
        {
            FRW_TIMER_CREATE_TIMER(&pst_pm_handler->st_inactive_timer,
                                   dmac_pm_ap_inactive_timer,
                                   AP_PWR_DEFAULT_USR_CHECK_TIME,      /* 1000ms触发一次 */
                                   (oal_void*)pst_pm_handler,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   ul_core_id);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_work_exit
 功能描述  : work状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_work_exit(oal_void *p_ctx)
{
    mac_pm_handler_stru *pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return;
    }
    else if (OAL_TRUE == pst_pm_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_pm_handler->st_inactive_timer);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_work_event
 功能描述  : work状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_work_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_INACTIVE:
        case AP_PWR_EVENT_NO_USR:
            if(pst_pm_handler->bit_pwr_wow_en)
            {
                dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WOW);
            }
            else
            {
                dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_IDLE);
            }
        break;
        case AP_PWR_EVENT_USR_ASSOC:
            pst_pm_handler->ul_user_check_count = 0;
        break;
        case AP_PWR_EVENT_WIFI_DISABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_DEEP_SLEEP);
            break;
        default:

        /* OAM日志中不能使用%s*/
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;

    }
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : ap_power_state_deep_sleep_entry
 功能描述  : deep_sleep状态的entry接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_deep_sleep_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_deep_sleep_exit
 功能描述  : deep_sleep状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_deep_sleep_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_deep_sleep_event
 功能描述  : deep_sleep状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_deep_sleep_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_WIFI_ENABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WORK);
        break;
        default:
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : ap_power_state_wow_entry
 功能描述  : wow状态的entry接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_wow_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_wow_exit
 功能描述  : wow状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_wow_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_wow_event
 功能描述  : wow状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_wow_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : ap_power_state_idle_entry
 功能描述  : idle状态的entry接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_idle_entry(oal_void *p_ctx)
{
    /*IDLE状态下:
    VAP层面调整beacon周期到1s,发送功率调整到最大功率降12db。
    device层面在hal层关闭1路接收发送通路(见mac_pm_set_hal_state)，开启PCIE L1-S低功耗，mem-prechargre，soc总线自动门控*/

    /* 设置beacon period, 原本每VAP可设，因为约束device下VAP的beacon值一样，放在mac_pm_set_hal_state中实现*/

    /*发射功率调整在tbtt中断处理中*/

    /*device低功耗设置在mac_pm_set_hal_state中完成*/

    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_idle_exit
 功能描述  : idle状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_idle_exit(oal_void *p_ctx)
{

    return;

}

/*****************************************************************************
 函 数 名  : ap_power_state_idle_event
 功能描述  : idle状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_idle_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_USR_ASSOC:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WORK);
        break;
        case AP_PWR_EVENT_WIFI_DISABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_DEEP_SLEEP);
            break;
        default:
            /* OAM日志中不能使用%s*/
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : ap_power_state_off_entry
 功能描述  : off状态的entry接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_off_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_off_exit
 功能描述  : off状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_off_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_off_event
 功能描述  : off状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_off_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_pm_post_event
 功能描述  : 节能状态机的事件处理接口,节能状态机的状态切换以事件来驱动，基于frw的事件分发机制来承载pm的内部事件
 输入参数  : pst_event_mem: frw的事件结构指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_pm_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data)
{
    mac_pm_handler_stru  *pst_handler;
    mac_fsm_stru         *pst_fsm;
    oal_uint32            ul_ret;
    dmac_vap_stru*        pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    if(pst_dmac_vap == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }
    pst_handler = pst_dmac_vap->pst_pm_handler;
    if(pst_handler == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }

    pst_fsm = pst_handler->p_mac_fsm;
    ul_ret = mac_fsm_event_dispatch(pst_fsm,us_type,us_datalen,pst_data);

    return ul_ret;

}

/*****************************************************************************
 函 数 名  : dmac_pm_state_trans
 功能描述  : PM节能状态机的状态切换接口
 输入参数  : pst_handler:pm handler指针
             uc_state:切换状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_void dmac_pm_state_trans(mac_pm_handler_stru* pst_handler,oal_uint8 uc_state)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    mac_device_stru *pst_mac_dev;
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_fsm->p_oshandler);
    pst_mac_dev  =  mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if(uc_state>=PWR_SAVE_STATE_BUTT)
    {
        /* OAM日志中不能使用%s*/
        OAM_ERROR_LOG1(pst_mac_dev->uc_cfg_vap_id, OAM_SF_PWR, "hmac_pm_state_trans:invalid state %d",uc_state);
        return;
    }

    mac_fsm_trans_to_state(pst_fsm, uc_state);

    /*本fsm的状态已经切换了，向arbiter投票*/
    mac_pm_arbiter_to_state(pst_mac_dev, pst_handler->ul_pwr_arbiter_id,
                            DMAC_VAP2DEV_PM_STATE(pst_fsm->uc_prev_state),
                            DMAC_VAP2DEV_PM_STATE(pst_fsm->uc_cur_state));

    return;

}

/*****************************************************************************
 函 数 名  : dmac_pm_ap_inactive_timer
 功能描述  : AP类型VAP创建inactive定时器超时处理函数
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_uint32 dmac_pm_ap_inactive_timer(oal_void* pst_arg)
{
    mac_pm_handler_stru *pst_pm_handler = (mac_pm_handler_stru*)pst_arg;
    mac_fsm_stru        *pst_fsm;
    dmac_vap_stru       *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if((0 == pst_dmac_vap->st_vap_base_info.us_user_nums) &&
       (AP_PWR_MAX_USR_CHECK_COUNT <= pst_pm_handler->ul_user_check_count))
    {
        pst_fsm = pst_pm_handler->p_mac_fsm;
        mac_fsm_event_dispatch(pst_fsm,
                                AP_PWR_EVENT_NO_USR,
                                0, OAL_PTR_NULL);
    }
    else if(0 == pst_dmac_vap->st_vap_base_info.us_user_nums)
    {
       pst_pm_handler->ul_user_check_count++;
    }
    else
    {
        /*TBD:VAP流量检测，是否活跃*/
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_pm_ap_attach
 功能描述  : AP类型VAP创建pm handler
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
mac_pm_handler_stru * dmac_pm_ap_attach(oal_void* pst_oshandler)
{
    mac_pm_handler_stru *p_handler = OAL_PTR_NULL;
    mac_device_stru     *p_device;
    dmac_vap_stru       *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;
    oal_uint8            auc_fsm_name[6] = {0};


    if(OAL_PTR_NULL!=p_dmac_vap->pst_pm_handler)
    {
        return p_dmac_vap->pst_pm_handler;
    }

    p_handler = (mac_pm_handler_stru*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,OAL_SIZEOF(mac_pm_handler_stru),OAL_TRUE);
    if(OAL_PTR_NULL == p_handler)
    {
        OAM_ERROR_LOG0(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ap_pm_attach:malloc memory for pm handler fail!");
        return OAL_PTR_NULL;
    }

    OAL_MEMZERO(p_handler, OAL_SIZEOF(mac_pm_handler_stru));

    p_handler->bit_pwr_sleep_en     = 0;
    p_handler->bit_pwr_siso_en      = OAL_TRUE;
    p_handler->bit_pwr_wow_en       = 0;
    p_handler->ul_inactive_time     = 0;
    p_handler->ul_user_check_count  = 0;
    p_handler->ul_max_inactive_time = AP_PWR_DEFAULT_INACTIVE_TIME;
    p_handler->ul_idle_beacon_txpower   = 0xf2;

    /* 准备一个唯一的fsmname */
    auc_fsm_name[0] = (oal_uint8)p_dmac_vap->st_vap_base_info.ul_core_id;
    auc_fsm_name[1] = p_dmac_vap->st_vap_base_info.uc_chip_id;
    auc_fsm_name[2] = p_dmac_vap->st_vap_base_info.uc_device_id;
    auc_fsm_name[3] = p_dmac_vap->st_vap_base_info.uc_vap_id;
    auc_fsm_name[4] = p_dmac_vap->st_vap_base_info.en_vap_mode;
    auc_fsm_name[5] = 0;

    p_handler->p_mac_fsm = mac_fsm_create((oal_void*)p_dmac_vap,
                                          auc_fsm_name,
                                          p_handler,
                                          PWR_SAVE_STATE_WORK,
                                          g_ap_power_fsm_info,
                                          OAL_SIZEOF(g_ap_power_fsm_info)/OAL_SIZEOF(mac_fsm_state_info)
                                          );


    p_device = mac_res_get_dev(p_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == p_device)
    {
        OAM_ERROR_LOG1(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ap_pm_attach: vap state[%d]!",
                       p_dmac_vap->st_vap_base_info.en_vap_state);
        return OAL_PTR_NULL;
    }
    p_handler->ul_pwr_arbiter_id    = mac_pm_arbiter_alloc_id(p_device,p_handler->p_mac_fsm->uc_name,MAC_PWR_ARBITER_TYPE_AP);

    p_dmac_vap->pst_pm_handler = p_handler;

    return  p_dmac_vap->pst_pm_handler;

}

/*****************************************************************************
 函 数 名  : dmac_pm_ap_deattach
 功能描述  : AP类型VAP销毁pm handler
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_ap_deattach(oal_void* pst_oshandler)
{
    mac_pm_handler_stru *p_handler = OAL_PTR_NULL;
    mac_device_stru     *p_device;
    dmac_vap_stru       *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    p_handler = p_dmac_vap->pst_pm_handler;
    if(!p_handler)
    {
        return;
    }

    /*立刻切换到work状态*/
    dmac_pm_state_trans(p_handler, PWR_SAVE_STATE_WORK);

    if (OAL_TRUE == p_handler->st_inactive_timer.en_is_registerd)
     {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&p_handler->st_inactive_timer);
     }

    if(p_handler->p_mac_fsm)
    {
        mac_fsm_destroy(p_handler->p_mac_fsm);
    }

    p_device = mac_res_get_dev(p_dmac_vap->st_vap_base_info.uc_device_id);

    mac_pm_arbiter_free_id(p_device,p_handler->ul_pwr_arbiter_id);

    OAL_MEM_FREE(p_handler,OAL_TRUE);

    p_dmac_vap->pst_pm_handler = OAL_PTR_NULL;

    return;

}

/*****************************************************************************
 函 数 名  : dmac_pm_current_state
 功能描述  : PM节能状态机的当前状态
 输入参数  : pst_handler:pm handler指针
             uc_state:切换状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint8 dmac_pm_vap_current_state(oal_void* pst_oshandler)
{
    mac_pm_handler_stru     *pst_pm_handler = ((dmac_vap_stru*)pst_oshandler)->pst_pm_handler;
    mac_fsm_stru            *pst_fsm ;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return PWR_SAVE_STATE_BUTT;
    }

    pst_fsm = pst_pm_handler->p_mac_fsm;
    if(OAL_PTR_NULL == pst_fsm)
    {
        return PWR_SAVE_STATE_BUTT;
    }

    return pst_fsm->uc_cur_state;

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

