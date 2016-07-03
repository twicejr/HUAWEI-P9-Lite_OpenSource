
#ifndef __WAKELOCK_H__
#define __WAKELOCK_H__

#include <bsp_wakelock.h>
/************************************************************************
*时钟模块调试接口
************************************************************************/
void debug_wake_lock(PWC_CLIENT_ID_E id);
void debug_wake_unlock(PWC_CLIENT_ID_E id);
#endif
