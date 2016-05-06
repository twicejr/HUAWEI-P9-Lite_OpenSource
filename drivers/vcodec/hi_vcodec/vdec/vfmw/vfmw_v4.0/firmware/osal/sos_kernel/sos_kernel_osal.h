/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDaRH/mYdIijFrTqr/UaRBfB2ylm29ZtemC0p1r
w4HAPZDg7CZHVO7OeWdV9RjDXmaqi9pg/K0L2WeHMQwYuJ60tQQFERUjwnO7P0sDjHaExkBj
Sw7pEC7CPZoIzOnyYWhGLqs0TGvwHp3G3mXNO3TIPKBbFe8dlgj+4cd8xhLosA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

#ifndef __VFMW_SOS_HEADER__
#define __VFMW_SOS_HEADER__

#include "sre_hwi.h"
#include "debug.h"
#include "sre_mem.h"
#include "sre_task.h"
#include "sre_ticktimer.h"
#include "sre_base.h"
#include "boot.h"
#include "sre_sem.h"
#include "sre_debug.h"
#include "sre_sys.h"
#include "sre_securemmu.h"
#include "init_ext.h"
#include "vfmw_osal_ext.h"


/*======================================================================*/
/*                            struct define                             */
/*======================================================================*/
typedef SINT32     OSAL_FILE;
typedef SINT32*    OSAL_TASK;

typedef struct
{
    SINT32         irq_lock;
    unsigned long  irq_lockflags;
    SINT32         isInit;
} SOS_IRQ_SPIN_LOCK;


/*======================================================================*/
/*                         secure os extern function                    */
/*======================================================================*/
extern int   snprintf(char *str, int sz, const char *fmt, ...);
extern void* memmove(void *dest, const void *src, unsigned long count);
extern int   uart_printf_func(const char *fmt, ...);

/*======================================================================*/
/*                         secure os function declare                   */
/*======================================================================*/
SINT8* SOS_MapShare(UINT32 Phy, SINT32 Size, UINT32 SecMode, UINT32 IsCached);
SINT32 SOS_UnMapShare(VOID *Vir, SINT32 Size);


#endif


