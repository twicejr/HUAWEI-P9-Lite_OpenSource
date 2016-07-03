#ifndef __MDRV_CCORE_ANTEN_H__
#define __MDRV_CCORE_ANTEN_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_pm_common.h>

/*共天线特性模式设置。*/
typedef enum tagGPIO_ANT_MODESET_E
{
    ANT_LTE = 0,
    ANT_GSM = 1,
    ANT_MAX
} GPIO_ANT_MODESET_E;

/*fem io ctrl type宏定义*/
typedef enum{
    CFG_RFFE_GROUP_GPIO_MIPI = 1,/*按照射频18002 配置fem 管脚*/
    CFG_RFFE_SET_PIN_NO_NV,      /*上层管脚配置，不依懒nv*/
    CFG_RFFE_SET_PIN_WITH_RESUEM,
    CFG_RFFE_3RDMODEM_IS_ACTIVE,     /*是否有外置modem在位*/
    FEMIO_CTRL_TYPE_BUTT
}FEMIO_CTRL_TYPE;

/*****************************************************************************
     *  函 数 名  : mdrv_anten_get_lockstate
     *  功能描述  :  获取有线与无线的连接状态。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_anten_get_lockstate (PWC_COMM_MODEM_E modem_id,unsigned int *status);

/*****************************************************************************
     *  函 数 名  : mdrv_anten_register_intr_cb
     *  功能描述  :  设置回调函数，用于获取天线状态。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
void mdrv_anten_register_intr_cb (PWC_COMM_MODEM_E modem_id,void* routine, int para);

/*****************************************************************************
     *  函 数 名  : mdrv_anten_set_outer_rfswitch
     *  功能描述  :  外接Modem的天线选择控制接口。NAS专用。
     *  输入参数  : status: 1：外接Modem天线功能；
        *                                       0：内置Modem天线功能。
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_anten_set_outer_rfswitch (unsigned int status);

/*****************************************************************************
     *  函 数 名  : mdrv_anten_get_outer_rfswitch
     *  功能描述  :  外接Modem的天线选择查询接口。NAS专用。
     *  输入参数  :
     *
     *  输出参数  : status: 1：外接Modem天线功能；
        *                                       0：内置Modem天线功能。
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_anten_get_outer_rfswitch (unsigned int *status);

/*****************************************************************************
     *  函 数 名  : 主副卡共天线特性设置接口。主卡LTE有两个天线：主集和分集。
     *                         分集天线可以与GSM共用。G模可以调用这个接口设置分集天线给GSM使用。
     *                         GUDSP专用。
     *  功能描述  :  mdrv_anten_set_mode
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_anten_set_mode (GPIO_ANT_MODESET_E status);

/*****************************************************************************
     *  函 数 名  : mdrv_rf_set_pin_highz
     *  功能描述  :  配置射频相关的管脚配置值功能。GUDSP专用。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_rf_set_pin_highz (unsigned char mask, unsigned char is_hz, unsigned char value);

/*****************************************************************************
     *  函 数 名  : mdrv_rf_enable_rse
     *  功能描述  : 主副卡天线开关存在干扰导致RSE超标问题规避新增接口，RSE功能打开，GUDSP专用。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_rf_enable_rse (void);

/*****************************************************************************
     *  函 数 名  : mdrv_rf_disable_rse
     *  功能描述  :  主副卡天线开关存在干扰导致RSE超标问题规避新增接口，RSE功能关闭，GUDSP专用。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
        *                           其他    操作失败。
          *
     ******************************************************************************/
int mdrv_rf_disable_rse (void);



int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3);

#ifdef __cplusplus
}
#endif
#endif

