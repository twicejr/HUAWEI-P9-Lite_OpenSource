#include <hi_base.h>
#include <hi_timer.h>
#include <soc_interrupts_m3.h>
#include <soc_clk.h>
#include "cmsis_os.h"

/*ºê¶¨Òå*/
#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif
#define NOT_ACTIVE  1

#define TIMER_FALSE 0
#define TIMER_TRUE  1

#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif

#ifndef SEM_FULL
#define SEM_FULL 1
#endif
#define TIMER_LOADCOUNT(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_LOADCOUNT_OFFSET )
#define TIMER_LOADCOUNT_H(hard_timer_id_addr)                     (hard_timer_id_addr + HI_TIMER_LOADCOUNT_H_OFFSET )
#define TIMER_CURRENTVALUE(hard_timer_id_addr)                    (hard_timer_id_addr + HI_TIMER_CURRENTVALUE_OFFSET )
#define TIMER_CURRENTVALUE_H(hard_timer_id_addr)                  (hard_timer_id_addr +  HI_TIMER_CURRENTVALUE_H_OFFSET)
#define TIMER_CONTROLREG(hard_timer_id_addr)                      (hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET )
#define TIMER_EOI(hard_timer_id_addr)                             (hard_timer_id_addr +  HI_TIMER_EOI_OFFSET)
#define TIMER_INTSTATUS(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_INTSTATUS_OFFSET )

#define SOFTTIMER_MAX_LENGTH             (0xFFFFFFFF>>15)
#define ELAPESD_TIME_INVAILD             0xFFFFFFFF

#define TIMERn_EN_ACK                      (1<<4)
#define TIMERn_INT_MASK                    (1<<2)
#define TIMERn_MODE_PERIOD                 (1<<1)
#define HARD_TIMER_ENABLE                  1
#define HARD_TIMER_DISABLE                 0
#define TIMER_ONCE_COUNT                   0
#define TIMER_PERIOD_COUNT                 1


