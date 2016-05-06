
#ifndef __BSP_HW_SPINLOCK_H__
#define __BSP_HW_SPINLOCK_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <osl_irq.h>


#define HW_SPINLOCK_WAIT_FOREVER    (-1)
#define HW_MEMREPAIR_LOCKID         (0x4)
#define HW_PMUCLK_LOCKID         (0x9)
#define HW_GPIO_LOCKID         (0x1)

/*****************************************************************************
* 函数  : hwspin_trylock
* 功能  : 尝试获取一个硬件锁
* 输入  : 硬件锁ID
* 输出  : 无
* 返回  : 成功返回0
* 注意事项: 该硬件锁只能保证核间互斥，核内的互斥需要调用者保证
*****************************************************************************/
int hwspin_trylock(u32 id);

/*****************************************************************************
* 函数  : hwspin_unlock
* 功能  : 尝试获取一个硬件锁
* 输入  : 硬件锁ID
* 输出  : 无
* 返回  : 成功返回0
* 注意事项: 无
*****************************************************************************/
int hwspin_unlock(u32 id);

/*****************************************************************************
* 函数  : hwspin_lock_timeout
* 功能  : 尝试获取一个硬件锁
* 输入  : id        硬件锁ID
          time_us   以微妙为单位的延时时间，永久等待请使用HW_SPINLOCK_WAIT_FOREVER
* 输出  : 无
* 返回  : 成功返回0
* 注意事项: 无
*****************************************************************************/
int hwspin_lock_timeout(u32 id, int time_us);


void hwspinlock_init(void);

#ifdef __cplusplus
}
#endif

#endif

