/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  acc_bus_stress.c
*
*   作    者 :  w00228729
*
*   描    述 :  完成组包加速功能压力测试
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 修改
*************************************************************************/
#include "securec.h"
#include <osl_sem.h>
#include <osl_thread.h>
#include <osl_malloc.h>
#include <mdrv_cipher.h>
#include <bsp_busstress.h>
#include <bsp_softtimer.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include <acc_balong.h>
#include <cipher_balong.h>
#include <c_sys_bus_pressure.h>

#define ACC_CHN 0
#define	PKT_LEN		0x800		/*MAX:0xfff8*/
#define EXTREME_PRESSURE
#define	ACC_TIMER_RATIO	(32768)					/*one second*/
#define	ACC_RD_TMOUT	(2 * ACC_TIMER_RATIO)   /*must less than 16 second*/
#define	ACC_LEN_RATIO	(1024*1024)
#define ACC_ERROR	-1
#define	ACC_SUCCESS 0
#define acc_print(fmt, ...) bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, \
											fmt, ##__VA_ARGS__)

static unsigned int g_ChnBusy = 0;
static struct softtimer_list acc_timer_id;
static osl_sem_id acc_test_sem;
static ACC_SINGLE_CFG_S *pstCfg = NULL;
static void *pInAddr  = NULL;
static void *pOutAddr = NULL;
static OSL_TASK_ID acc_taskid1 = 0,acc_taskid2 = 0,acc_taskid3 = 0;
osl_sem_id acc_sema;

int cipher_bus_routine_run = 1;

unsigned int g_acc_busstress_test_ok_cnt = 0;
unsigned int g_acc_busstress_test_fail_cnt = 0;
unsigned int show_rate = 0;
extern struct acc_chn_ctl acc_ctl;
struct acc_debug {
	/*acc rate*/
	unsigned int show_rate;
	unsigned int time_cnt;
	unsigned int length_cnt;
	unsigned int record_length;
	unsigned int rate;

	/*acc status*/
	unsigned int sem_count;
	unsigned int stress_success;
	unsigned int stress_failed;
};
struct acc_debug g_acc_info;
void acc_enable_show_rate(unsigned int en)
{
    g_acc_info.show_rate = en;
    return;
}
int acc_show_rate(void)
{	
	unsigned int rate = 0;
	unsigned int rd_len = 0;
	unsigned int rd_ts =  0;
	unsigned int ratio = ACC_LEN_RATIO / (ACC_TIMER_RATIO * 8);
	if(!g_acc_info.show_rate) {
		return ACC_ERROR;
	}
	rd_ts =  bsp_get_slice_value() - g_acc_info.time_cnt;
	if(rd_ts < ACC_RD_TMOUT) {
		return ACC_ERROR;
	}
	rd_len = g_acc_info.record_length - g_acc_info.length_cnt;
	g_acc_info.time_cnt = bsp_get_slice_value();
	g_acc_info.length_cnt = g_acc_info.record_length;
	if(rd_len <= 0 || rd_ts <= 0) {
		acc_print("acc len or ts err!\n");
		return ACC_ERROR;
	} else {
		rate = rd_len / (rd_ts * ratio);
		acc_print("ACC rate:%uMbps\n", rate);
	}
	return ACC_SUCCESS;
}
int acc_ddr_data_init(unsigned int u32BlockLen, unsigned int u32PakNums,
	void **pInAddr, void **pOutAddr,ACC_SINGLE_CFG_S ** pstCfg)
{
    int i;
    char * ptempIn;

    *pstCfg = (ACC_SINGLE_CFG_S *)osl_cachedma_malloc(sizeof(ACC_SINGLE_CFG_S));
    if(!*pstCfg)
    {
        acc_print("pstCfg malloc failed !\n");
        return ERROR;
    }
    
    *pInAddr = (void *)osl_cachedma_malloc(u32BlockLen * u32PakNums);
    if(NULL == *pInAddr)
    {
        osl_cachedma_free(*pstCfg);
        acc_print("pInAddr malloc failed !\n");
        return ERROR;
    }
    
    *pOutAddr = (void *)osl_cachedma_malloc(u32BlockLen * u32PakNums);
    if(NULL == *pOutAddr)
    {
        osl_cachedma_free(*pstCfg);
        osl_cachedma_free(*pInAddr);
        acc_print("pOutAddr malloc failed !\n");
        return ERROR;
    }

    ptempIn = *pInAddr;
    for(i = 0; i <(int) (u32BlockLen * u32PakNums); i ++)
    {
        *ptempIn = (char)(i % 255);
        ptempIn++;
    }
    memset_s(*pOutAddr, u32BlockLen * u32PakNums, 0, u32BlockLen * u32PakNums);
    
    return OK;
}

void acc_timer_event(unsigned int parm)
{
	osl_sem_up(&acc_test_sem);
	bsp_softtimer_add(&acc_timer_id);
}

#ifdef EXTREME_PRESSURE
void acc_bd_done_int(unsigned int chn_id, unsigned int s_addr, 
	unsigned int d_addr,CIPHER_NOTIFY_STAT_E en_status, unsigned int private)
{
	if (chn_id == ACC_CHN) {
		osl_sem_up(&acc_sema);
		g_acc_info.sem_count++;
	}
}

int acc_stress_test_routine(void * par)
{
    int s32ret;
    int i = 0;
	unsigned int total_len;
    unsigned int u32BdFifoAddr;
	unsigned int record_flag = 0;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;

	osl_sem_init(SEM_FULL, &acc_sema);
	mdrv_cipher_register_notify_cb(acc_bd_done_int);
	u32BdFifoAddr = (unsigned int)acc_ctl.fifo_base[0];	
	pTempInAddr  = pInAddr;
	pTempOutAddr = pOutAddr;
	total_len = PKT_LEN * (acc_ctl.fifo_depth - 2);
	for(i = 0; i < acc_ctl.fifo_depth - 2; i++)
    {
		pstCfg->u32BlockLen = PKT_LEN;
		pstCfg->u32Offset   = 0;
		pstCfg->u32OutLen   = PKT_LEN;
		pstCfg->bMemBlock   = 1;
		pstCfg->pInMemMgr   = pTempInAddr;
		pstCfg->pOutMemMgr  = pTempOutAddr;
        s32ret = mdrv_acc_dma(u32BdFifoAddr, pstCfg);
        if(OK != s32ret){
            acc_print("Configure acc fail，return = 0x%x\n", s32ret);
            return -1;
        }
        pTempInAddr  = (char *)((unsigned int)pTempInAddr  + PKT_LEN);
        pTempOutAddr = (char *)((unsigned int)pTempOutAddr + PKT_LEN);
    }

	/*Open acc bd done interrupt*/
	acc_enable_bd_done_int();
	
    while (cipher_bus_routine_run)
    {
		osl_sem_down(&acc_sema);
		if (!record_flag)
			record_flag = 1;
		else {
			g_acc_info.record_length += total_len;
			acc_show_rate();
		}
        s32ret = mdrv_acc_enable(ACC_CHN, u32BdFifoAddr);
        if(s32ret) {
        	g_acc_busstress_test_fail_cnt++;
			g_acc_info.stress_failed++;
            return ERROR;
        }
		g_acc_busstress_test_ok_cnt++;
		g_acc_info.stress_success++;
    }
    return OK;       
}
#else
int acc_stress_test_routine(void * par)
{
    int s32ret;
    unsigned int u32BdFifoAddr;
    void *pTempInAddr  = NULL;
    void *pTempOutAddr = NULL;
    int i = 0;

    while (cipher_bus_routine_run)
    {
        pTempInAddr  = pInAddr;
        pTempOutAddr = pOutAddr;
        osl_sem_down(&acc_test_sem);

        while(mdrv_acc_get_status(ACC_CHN) != CHN_FREE)
    	{
            g_ChnBusy ++;
			osl_task_delay(1);
    	}
		
        u32BdFifoAddr = mdrv_acc_get_bdq_addr();
        if(!u32BdFifoAddr)
        {
            acc_print("Get bdq addr failed，result = 0x%x\n", u32BdFifoAddr);
            return -1;
        }

        for(i = 0; i < acc_ctl.fifo_depth; i++)
        {
        	/*配置pstCfg信息*/
			pstCfg->u32BlockLen = PKT_LEN;
			pstCfg->u32Offset   = 0;
			pstCfg->u32OutLen   = PKT_LEN;
			pstCfg->bMemBlock   = 1;
			pstCfg->pInMemMgr   = pTempInAddr;
			pstCfg->pOutMemMgr  = pTempOutAddr;
            s32ret = mdrv_acc_dma(u32BdFifoAddr, pstCfg);
            if(OK != s32ret)
            {
                acc_print("mdrv_acc_dma failed，return:0x%x\n", s32ret);
                return -1;
            }
            pTempInAddr  = (char *)((unsigned int)pTempInAddr  + PKT_LEN);
            pTempOutAddr = (char *)((unsigned int)pTempOutAddr + PKT_LEN);
        }    

        s32ret = mdrv_acc_enable(ACC_CHN, u32BdFifoAddr);
        if(s32ret)
        {
        	g_acc_busstress_test_fail_cnt++;
            acc_print("ACC enable failed，return:0x%x\n", s32ret);
            return ERROR;
        }
			g_acc_busstress_test_ok_cnt++;
    }

    return OK;       
}

#endif
void sys_acc_start(struct master* master)
{
	int s32ret = 0;
    int test_type = 0; //Todo:
    int test_rate = 8;
	acc_timer_id.func      = acc_timer_event;
	acc_timer_id.para      = 0;
	acc_timer_id.timeout   = test_rate;
	acc_timer_id.wake_type = SOFTTIMER_NOWAKE;

	if((DDR == test_type) ||(DDR_BBE16_AXIMEM == test_type))
	{
		s32ret = acc_ddr_data_init(PKT_LEN, acc_ctl.fifo_depth, &pInAddr, 
													&pOutAddr,&pstCfg);
		if(s32ret)
		{
		    return ;
		}
	}
	osl_sem_init(SEM_EMPTY, &acc_test_sem);
	//set_test_switch_stat(ACC, TEST_RUN);
	cipher_bus_routine_run = 1;

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&acc_timer_id))
	{
		acc_print("SOFTTIMER_CREATE_TIMER fail.\n");
		return ; 
	}
	if((DDR == test_type) ||(DDR_BBE16_AXIMEM == test_type))
	{
	    /*acc_stress_test_start = 10;*/
		s32ret = osl_task_init("accTestInDdr", 10, 1024, 
					(OSL_TASK_FUNC)acc_stress_test_routine, 0, &acc_taskid1);
		if (ERROR == s32ret)
	    {
	        acc_print("Task init failed，s32ret:%d\n", s32ret);
	        return ;
	    }
	}

	bsp_softtimer_add(&acc_timer_id);

    return ;    
}

void sys_acc_stop(struct master* master)
{
	//set_test_switch_stat(ACC, TEST_STOP);
	cipher_bus_routine_run = 0;
	while((OK == osl_task_check(acc_taskid1)) ||
		(OK == osl_task_check(acc_taskid2))   ||
		(OK == osl_task_check(acc_taskid3)))
		osl_task_delay(100);
	osl_sema_delete(&acc_test_sem);
	if(acc_timer_id.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&acc_timer_id);
		bsp_softtimer_free(&acc_timer_id);
	}
	osl_cachedma_free(pstCfg);
	osl_cachedma_free(pInAddr);
	osl_cachedma_free(pOutAddr);
	return ;
}
void sys_acc_report(struct master* master)
{
	acc_print("acc chn busy :%d\n", g_ChnBusy);
	acc_print("acc succeed  :%d\n", g_acc_info.stress_success);
	acc_print("acc failed   :%d\n", g_acc_info.stress_failed);
	acc_print("acc semaphore:%d\n", g_acc_info.sem_count);
}

void sys_acc_init(struct master* master)
{
    master->start = sys_acc_start;
    master->stop = sys_acc_stop;
    master->record = NULL;
    master->report = sys_acc_report;
}

