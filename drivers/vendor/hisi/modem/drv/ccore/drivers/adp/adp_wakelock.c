/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_wakelock.c
*
*   作    者 :  xujingcui x00221564
*
*   描    述 :  睡眠投票模块适配文件
*
*   修改记录 :
*
*************************************************************************/
#include "mdrv_pm.h"
#include "bsp_wakelock.h"

unsigned int mdrv_pm_wake_lock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_lock(&lock);
    return 0;
}
unsigned int mdrv_pm_wake_unlock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_unlock(&lock);
    return 0;
}

