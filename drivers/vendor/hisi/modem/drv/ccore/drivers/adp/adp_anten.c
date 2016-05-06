#include <product_config.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <drv_nv_def.h>
#include <hi_anten.h>
#include <gpio_balong.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <bsp_version.h>
#include <bsp_rf_balong.h>


/*****************************************************************************
 函 数 名  : drv_anten_lock_status_get
 功能描述  : 获取有线与无线的连接状态
 输入参数  : none
 输出参数  : 0 - 无线连接
             1 - 有线连接
 返 回 值  : 0 - 成功
             其它为失败

*****************************************************************************/
int mdrv_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    return bsp_anten_get_lockstate(modem_id,status);
}


/*****************************************************************************
 函 数 名  : drv_anten_int_install
 功能描述  : 中断注册函数，用来获得当前的天线状态
 输入参数  : routine   - 中断处理函数
             para      - 保留字段
 输出参数  : none
 返 回 值  : void

*****************************************************************************/
void mdrv_anten_register_intr_cb(PWC_COMM_MODEM_E modem_id, void* routine, int para)
{
    bsp_anten_int_install(modem_id, routine, para);
}
/*****************************************************************************
* 函 数    : mdrv_anten_set_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择控制接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 输 出    : 无

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int mdrv_anten_set_outer_rfswitch(unsigned int status)
{   
    return bsp_anten_set_outer_rfswitch(status);
}
/*****************************************************************************
* 函 数    : mdrv_anten_set_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择查询接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : 无

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int mdrv_anten_get_outer_rfswitch(unsigned int *status)
{
    return bsp_anten_get_outer_rfswitch(status);
}
/*****************************************************************************
* 函 数    : mdrv_anten_set_mode
* 功 能    : DSP专用接口,GPIO共天线设置
* 输 入    : @mode:天线模式
*                   ANT_LTE     =  0, lte分集天线
*                   ANT_GSM     =  1, GSM副卡天线

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0:正确，-1:错误
* 作 者    : z00228752
*****************************************************************************/
int mdrv_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    return bsp_anten_set_mode(mode);
}

/*****************************************************************************
* 函 数    : mdrv_fem_ioctrl
* 功 能    : 射频管脚配置
* 输 入    : @ctrl_type  接口类型，
              1为gpio、mipi参照NV配置，
              2为直接传参配置
              3在2的基础上会将配置在低功耗唤醒时恢复
              4表示VIA MODEM是否在位

               ctrl_type = CFG_RFFE_GROUP_GPIO_MIPI
              @para1 is nvindex      nv  项索引，取值为0-15，此参数参见nv手册18002
              @para2 is mux          管脚复用配置，0为gpio功能，1为线控功能
              @para3 is reserved     保留

               ctrl_type = CFG_RFFFE_SET_PIN_NO_NV
              @para1 is gpio num     gpio编号
              @para2 is mux          管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value        若para2为gpio功能，则value为输出电平

               ctrl_type = CFG_RFFE_SET_PIN_WITH_RESUEM(在1的基础上，增加低功耗功能)
              @para1 is gpio num     gpio编号
              @para2 is mux          管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value        若para2为gpio功能，则value为输出电平

               ctrl_type = CFG_VIA_MODEM_IS_ACTIVE(外置modem是否在位)
              @para1 is active       0表示不在位，1表示在位
              @para2 is mux          保留
              @para3 is value        保留

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 此接口在手机平台使用，MBB不设及，打桩即可
*****************************************************************************/
int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return bsp_fem_ioctrl(ctrl_type,para1,para2,para3);
}

