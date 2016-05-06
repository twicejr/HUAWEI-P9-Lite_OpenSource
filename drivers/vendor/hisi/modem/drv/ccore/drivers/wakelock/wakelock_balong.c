/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  wakelock_balong.c
*
*   作    者 :  xujingcui x00221564
*
*   描    述 :  睡眠投票模块
*
*   修改记录 :
*
*************************************************************************/
#include <osl_thread.h>
#include <bsp_dump.h>
#include <bsp_wakelock.h>
#include <bsp_pm_om.h>
#include <bsp_hardtimer.h>
#include "wakelock.h"
/*此全局变量用于记录投票情况，每bit代表一票*/
static unsigned int has_wakelock = 0;
static char *wakelock_dump_addr;
void wakelock_show(void);


enum lock_enum{
	WAKE_UNLOCK,
	WAKE_LOCK,
};

struct wakelock_om_s{
	u32 stamp;
	u32 lock_id;
	u32 lock_type;
	u32 lock_state;
	int cur_task_id;
}wakelock_dump_log={0,0,0,0,0};

struct wakelock_om_s *record=&wakelock_dump_log;

void bsp_wakelock_init(void){
	void* dump_base_addr = NULL;
	dump_base_addr=bsp_pm_dump_get(PM_OM_WAKE,sizeof(struct wakelock_om_s));
	if(dump_base_addr){
		record = (struct wakelock_om_s*)dump_base_addr;
	}

	dump_base_addr = NULL;
	dump_base_addr = (void *)bsp_dump_register_field(DUMP_CP_DRX, "DRX_CCORE", 0, 0, PM_DUMP_CCORE_DRX_SIZE, 0);
	if(dump_base_addr){
		wakelock_dump_addr = dump_base_addr;
	}
}
void wake_lock_init(struct wake_lock *lock, int lock_id, const char *name)
{
    if (!lock){
        vote_printf("This wakelock is NULL !! \n");
        return;
    }
    if((lock_id < PWRCTRL_SLEEP_BEGIN )||(lock_id >= LOCK_ID_BOTTOM))
    {
        vote_printf("wakelock lock_id define error,wake_lock_init is failure!! \n");/* [false alarm]:误报 dead code*/
        return;
    }
    if (name)
            lock->name = name;
    lock->lockid = (unsigned int)lock_id;
    return;
}
static inline void wakelock_dump_log_record(enum lock_enum type,struct wake_lock *lock){
     record->stamp= bsp_get_slice_value();
     record->lock_id = lock->lockid - PWRCTRL_SLEEP_BEGIN;
     record->lock_type = (u32)type;
     record->cur_task_id= osl_task_self();
     record->lock_state = has_wakelock;
     (void)bsp_pm_log_type(PM_OM_WAKE,0,sizeof(struct wakelock_om_s),(void*)record);
}
void wake_lock(struct wake_lock *lock)
{
    unsigned long flags = 0;
    int lockid = 0,temp = 0;
    temp = LOCK_ID_BOTTOM-PWRCTRL_SLEEP_BEGIN;/*lint !e656*/
    if (!lock){/*lint !e525*/
        vote_printf("This wakelock is NULL !! \n");
        return;
   }/*lint !e525*/
    lockid = (int)lock->lockid-PWRCTRL_SLEEP_BEGIN;
    if((lockid < 0 )||(lockid >= temp ))
    {
        vote_printf("wakelock lock_id define error,wake_lock is failure!! lock_id = 0x%x\n",lockid);
        return;
    }
    local_irq_save(flags);
   if (has_wakelock & ((unsigned int)0x1 << lockid)){
        //vote_printf("LOCK ID: %s ,has been locked!! \n", lock->name);
   }else{
        has_wakelock |= (unsigned int)((unsigned int)0x1 << lockid);
        if(wakelock_dump_addr)
            *((u32 *)wakelock_dump_addr)= has_wakelock;
   }
    wakelock_dump_log_record(WAKE_LOCK,lock);
    local_irq_restore(flags);
    return;
}
void wake_unlock(struct wake_lock *lock)
{
    unsigned long flags = 0;
    int lockid = 0,temp = 0;
    temp = LOCK_ID_BOTTOM-PWRCTRL_SLEEP_BEGIN;/*lint !e656*/
    if (!lock){
        vote_printf("This wakelock is NULL !! \n");
        return;
   }/*lint !e525*/
    lockid = (int)lock->lockid-PWRCTRL_SLEEP_BEGIN;;
    if((lockid < 0 )||(lockid >= temp))
    {
        vote_printf("wakelock lock_id define error,wake_unlock is failure!! \n");
        return;
    }
    local_irq_save(flags);
   if (has_wakelock & ((unsigned int)0x1 << lockid)){
        has_wakelock &= (unsigned int)(~((unsigned int)0x1 << lockid));
        if(wakelock_dump_addr)
            *((u32 *)wakelock_dump_addr)= has_wakelock;
   }else{
        //vote_printf("LOCK ID: %s, has been unlocked!! \n", lock->name);
   }
    wakelock_dump_log_record(WAKE_UNLOCK,lock);
    local_irq_restore(flags);
    return;
}
int wake_lock_active(struct wake_lock *lock)
{
    unsigned int lockid = 0;
    if (!lock){
        vote_printf("This wakelock is NULL !! \n");
        return -1;
    }
    lockid = lock->lockid-PWRCTRL_SLEEP_BEGIN;
    if (has_wakelock & ((unsigned int)0x1 << lockid)){
        return 1;
    }else{
        return 0;
    }
}
unsigned int  has_wake_lock(int type)
{
    return has_wakelock;
}

/*
*此函数用于产品线STANDYBY模式下清理所有投票
*其他场景请勿引用
*/
void all_vote_wake_unlock(void)
{
    has_wakelock = 0;
    return;
}
/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 功能描述  : AT^PSTANDBY
 输入参数  :
 输出参数  :
 返回值：
*****************************************************************************/
 unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime)
 {
	return 0;
 }
 unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime)
 {
	return 0;
 }



/**************************************************************************
*此处接口用于调试，请勿使用
***************************************************************************/
void debug_wake_lock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_lock(&lock);
}
void debug_wake_unlock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_unlock(&lock);
}

void wakelock_show(void)
{
   unsigned int i = 0,loop=0;
   unsigned int lockstat[32] = {0};
   unsigned int lockmap = has_wakelock;
   loop = LOCK_ID_BOTTOM-PWRCTRL_SLEEP_BEGIN;/*lint !e656*/
   for (i = 0; i < loop ; i++){
       if (lockmap & ((unsigned int)0x1 << i)){
           lockstat[i] = 1;
       }
   }
   
 
   /*
   *组件需要在此添加打印信息，用于查询所有组件的投票情况
   *请保证此打印顺序于drv_wakelock.h中的一致
   */
   vote_printf("All module vote status(1: oppose sleeping, 0: approve sleeping)\n");
   vote_printf("PWRCTRL_SLEEP_TLPS:          status: %d   LOCK_ID : %d\n", lockstat[0], PWRCTRL_SLEEP_TLPS);
   vote_printf("PWRCTRL_SLEEP_PS_G0:         status: %d   LOCK_ID : %d\n", lockstat[1], PWRCTRL_SLEEP_PS_G0);
   vote_printf("PWRCTRL_SLEEP_PS_W0:         status: %d   LOCK_ID : %d\n", lockstat[2], PWRCTRL_SLEEP_PS_W0);
   vote_printf("PWRCTRL_SLEEP_PS_G1:         status: %d   LOCK_ID : %d\n", lockstat[3], PWRCTRL_SLEEP_PS_G1);
   vote_printf("PWRCTRL_SLEEP_PS_W1:         status: %d   LOCK_ID : %d\n", lockstat[4], PWRCTRL_SLEEP_PS_W1);
   vote_printf("PWRCTRL_SLEEP_FTM:           status: %d   LOCK_ID : %d\n", lockstat[5], PWRCTRL_SLEEP_FTM);
   vote_printf("PWRCTRL_SLEEP_FTM_1:         status: %d   LOCK_ID : %d\n", lockstat[6], PWRCTRL_SLEEP_FTM_1);
   vote_printf("PWRCTRL_SLEEP_NAS:           status: %d   LOCK_ID : %d\n", lockstat[7], PWRCTRL_SLEEP_NAS);
   vote_printf("PWRCTRL_SLEEP_NAS_1:         status: %d   LOCK_ID : %d\n", lockstat[8], PWRCTRL_SLEEP_NAS_1);
   vote_printf("PWRCTRL_SLEEP_OAM:           status: %d   LOCK_ID : %d\n", lockstat[9], PWRCTRL_SLEEP_OAM);
   vote_printf("PWRCTRL_SLEEP_SCI0:          status: %d   LOCK_ID : %d\n", lockstat[10], PWRCTRL_SLEEP_SCI0);
   vote_printf("PWRCTRL_SLEEP_SCI1:          status: %d   LOCK_ID : %d\n", lockstat[11], PWRCTRL_SLEEP_SCI1);
   vote_printf("PWRCTRL_SLEEP_DMA:           status: %d   LOCK_ID : %d\n", lockstat[12], PWRCTRL_SLEEP_DMA);
   vote_printf("PWRCTRL_SLEEP_MEM:           status: %d   LOCK_ID : %d\n", lockstat[13], PWRCTRL_SLEEP_MEM);
   vote_printf("PWRCTRL_SLEEP_DSFLOW:        status: %d   LOCK_ID : %d\n", lockstat[14], PWRCTRL_SLEEP_DSFLOW);
   vote_printf("PWRCTRL_SLEEP_PM:            status: %d   LOCK_ID : %d\n", lockstat[15], PWRCTRL_SLEEP_TEST);
   vote_printf("PWRCTRL_SLEEP_UART0:         status: %d   LOCK_ID : %d\n", lockstat[16], PWRCTRL_SLEEP_UART0);
   vote_printf("PWRCTRL_SLEEP_TDS:           status: %d   LOCK_ID : %d\n", lockstat[17], PWRCTRL_SLEEP_TDS);
   vote_printf("PWRCTRL_SLEEP_CDMAUART:      status: %d   LOCK_ID : %d\n", lockstat[18], PWRCTRL_SLEEP_CDMAUART);
   vote_printf("PWRCTRL_SLEEP_USIM:          status: %d   LOCK_ID : %d\n", lockstat[19], PWRCTRL_SLEEP_USIM);
   vote_printf("PWRCTRL_SLEEP_DSPPOWERON:    status: %d   LOCK_ID : %d\n", lockstat[20], PWRCTRL_SLEEP_DSPPOWERON);
   vote_printf("PWRCTRL_SLEEP_RESET:         status: %d   LOCK_ID : %d\n", lockstat[21], PWRCTRL_SLEEP_RESET);
   vote_printf("PWRCTRL_SLEEP_PS_G2:         status: %d   LOCK_ID : %d\n", lockstat[22], PWRCTRL_SLEEP_PS_G2);
   vote_printf("PWRCTRL_SLEEP_FTM_2:         status: %d   LOCK_ID : %d\n", lockstat[23], PWRCTRL_SLEEP_FTM_2);
   vote_printf("PWRCTRL_SLEEP_NAS_2:         status: %d   LOCK_ID : %d\n", lockstat[24], PWRCTRL_SLEEP_NAS_2);
   vote_printf("PWRCTRL_SLEEP_1X:            status: %d   LOCK_ID : %d\n", lockstat[25], PWRCTRL_SLEEP_1X);
   vote_printf("PWRCTRL_SLEEP_HRPD:          status: %d   LOCK_ID : %d\n", lockstat[26], PWRCTRL_SLEEP_HRPD);
   vote_printf("PWRCTRL_SLEEP_MSP:           status: %d   LOCK_ID : %d\n", lockstat[27], PWRCTRL_SLEEP_MSP);
   vote_printf("wake lock:         debug_wake_lock(LOCK_ID)\n");
   vote_printf("wake unlock:       debug_wake_unlock(LOCK_ID)\n");
}


