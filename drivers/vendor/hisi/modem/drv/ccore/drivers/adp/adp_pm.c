/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : adp_pm.c */
/* Version       : 1.0 */
/* Created       : 2013-09-26*/
/* Last Modified : */
/* Description   :  pm adp*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#include <mdrv_pm.h>
#include <bsp_pm.h>/*ilnt !e322*/
/*
set&unset wakeup interrupt source
input : wake_src defined in drv_pm.h [DRV_PM_WAKE_SRC_ENUM]
*/
void mdrv_pm_set_wakesrc(PM_WAKE_SRC_E wake_src)
{
    pm_enable_wake_src(wake_src);
}

void mdrv_pm_clear_wakesrc(PM_WAKE_SRC_E wake_src)
{

    pm_disable_wake_src(wake_src);
}

/*先打桩处理*/
int mdrv_pm_register_sleep_ops(unsigned char* pname,PWC_SLEEP_FUNCPTR suspend,PWC_SLEEP_FUNCPTR resume){
    return pm_register_sleep_ops(pname,suspend,resume);

}

int mdrv_pm_unregister_sleep_ops(unsigned char* pname){
    return MDRV_ERROR;
}

