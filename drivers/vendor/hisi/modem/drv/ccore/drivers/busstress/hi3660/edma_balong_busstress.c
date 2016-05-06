#include "string.h"
#include "bsp_busstress.h"
#include "bsp_softtimer.h"
#include "bsp_edma.h"
#include "osl_sem.h"
#include "osl_malloc.h"
#include "osl_thread.h"
#include "osl_bio.h"
#include "bsp_sram.h"
#include "bsp_om.h"
#include "bsp_shared_ddr.h"

#define EDMA_MEMORY  EDMA_PWC_LDSP_TCM
#ifdef hiedmac_trace
#undef hiedmac_trace
#define hiedmac_trace(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))
#endif

#ifndef MEM_FOR_EDMAC_BUSSTRESS /* 需要在 bsp_busstress.h中定义 */
//#undef MEM_FOR_EDMAC_BUSSTRESS /* 需要在 bsp_busstress.h中定义 */
#define MEM_FOR_EDMAC_BUSSTRESS (HI_SHARED_DDR_BASE_ADDR + SHM_OFFSET_MDMA9_PM_BOOT)
#endif

#define EDMA_HANDLE_1_AXI_MEM_64_DST (MEM_FOR_EDMAC_BUSSTRESS)
#define EDMA_HANDLE_2_AXI_MEM_64_SRC (EDMA_HANDLE_1_AXI_MEM_64_DST + EDMA_TEST_LEN)
#define EDMA_HANDLE_2_AXI_MEM_64_DST (EDMA_HANDLE_2_AXI_MEM_64_SRC + EDMA_TEST_LEN)
#define EDMA_HANDLE_3_AXI_MEM_64_SRC (EDMA_HANDLE_2_AXI_MEM_64_DST + EDMA_TEST_LEN)


#define MEM_FOR_EDMAC2_BUSSTRESS (MEM_FOR_EDMAC_BUSSTRESS+4*EDMA_TEST_LEN)

#define EDMA2_HANDLE_1_AXI_MEM_64_DST (MEM_FOR_EDMAC2_BUSSTRESS)
#define EDMA2_HANDLE_2_AXI_MEM_64_SRC (EDMA2_HANDLE_1_AXI_MEM_64_DST + EDMA_TEST_LEN)
#define EDMA2_HANDLE_2_AXI_MEM_64_DST (EDMA2_HANDLE_2_AXI_MEM_64_SRC + EDMA_TEST_LEN)
#define EDMA2_HANDLE_3_AXI_MEM_64_SRC (EDMA2_HANDLE_2_AXI_MEM_64_DST + EDMA_TEST_LEN)


#define EDMA_HANDLE_NUM 1 /*(EDMA_MOVE_TYPE_BUTTOM) */


struct edma_busstress_info
{
    struct softtimer_list edma_softtimer_list;
    OSL_TASK_ID edma_stress_test_task_id ;
    osl_sem_id edma_send_sem ;
    AXI_DMA_TASK_HANDLE_S  stDMATaskHandle[EDMA_HANDLE_NUM];
    u8 EDMA_HANDLE_0_DDR_SRC[EDMA_TEST_LEN];
    u8 EDMA_HANDLE_0_DDR_DST[EDMA_TEST_LEN];
    u8 EDMA_HANDLE_1_DDR_SRC[EDMA_TEST_LEN];
    u8 EDMA_HANDLE_3_DDR_DST[EDMA_TEST_LEN];
};
struct edma_busstress_info g_edma_busstress_info ;

#if 0
/* edma 不依赖 busstress_balong.c 单独测试使用，*/
#define SENCE_NUM (4)
#define MODULE_NUM (20)

int   module_test_switch_stat[MODULE_NUM] = {0};


int get_test_switch_stat(int module_id)
{
	return module_test_switch_stat[module_id];
}

int set_test_switch_stat(int module_id, int run_or_stop)
{
	module_test_switch_stat[module_id] = run_or_stop;
	return 0;
}
#endif 

extern s32 EDMA_QueryCHNLState(u32 u32ChIdx);
extern s32 EDMA_NormTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
extern s32 EDMA_2VecTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
extern s32 EDMA_QueryCHNLState(u32 u32ChIdx);
extern s32 EDMA_QueryCHNsLState(u32 u32ChIdxMap);
extern int get_test_switch_stat(int module_id);

u32 g_edma_busstress_test_ok_cnt[EDMA_HANDLE_NUM] = {0};
u32 g_edma_busstress_test_fail_cnt[EDMA_HANDLE_NUM] = {0};

s32 edma_stress_test_routine()
{
    u32 count = 0;
    s32 s32ret = 0;
    u32 cur_idx = 0;

    while(get_test_switch_stat(EDMAC))
    {

        /*down(g_edma_busstress_info.edma_send_sem);*/
        osl_sem_down(&g_edma_busstress_info.edma_send_sem);

        if( 0 != EDMA_QueryCHNLState(EDMA_CHANNEL_START))
        {
            continue;
        }

        if(count > 0)
        {
            if(0 != memcmp( (void*)g_edma_busstress_info.stDMATaskHandle[cur_idx].u32DstAddr,\
                             (void*)g_edma_busstress_info.stDMATaskHandle[cur_idx].u32SrcAddr,EDMA_TEST_LEN) )
            {
                //hiedmac_trace("edma %d task,handle idx:%d,compare data fail.\n",count-1,cur_idx,0,0,0,0);
				g_edma_busstress_test_fail_cnt[cur_idx]++;
                //return -1;
                goto next_move;
            }
        }

        g_edma_busstress_test_ok_cnt[cur_idx]++;
 next_move:  cur_idx = count % EDMA_HANDLE_NUM;
        memset((void*)g_edma_busstress_info.stDMATaskHandle[cur_idx].u32SrcAddr,cur_idx,EDMA_TEST_LEN);
        memset((void*)g_edma_busstress_info.stDMATaskHandle[cur_idx].u32DstAddr,0xff,EDMA_TEST_LEN);
        s32ret = EDMA_NormTaskLaunch( &(g_edma_busstress_info.stDMATaskHandle[cur_idx]) );
        if(s32ret != 0)
        {
            hiedmac_trace("EDMA_NormTaskLaunch fail,ret:0x%x.\n",s32ret,0,0,0,0,0);
            continue;
        }

        count++;
		/* EDMA不执行DDR到BBE16DTCM的搬移 */
		//#define EDMA_MOVE_WITHOUT_DDR_TO_BBE16DTCM
		#ifdef EDMA_MOVE_WITHOUT_DDR_TO_BBE16DTCM
		if (EDMA_MOVE_DDR_TO_BBE16_DTCM == (count % EDMA_HANDLE_NUM))
		{
		    count++;
		    continue ;
		}
		#endif
    }

    return OK;
}

void edma_timer_event(u32 param)
{
    if((osl_sem_id) 0 != g_edma_busstress_info.edma_send_sem)
    {
        /*up(g_edma_busstress_info.edma_send_sem);*/
        osl_sem_up(&g_edma_busstress_info.edma_send_sem);
    }
    bsp_softtimer_add( &g_edma_busstress_info.edma_softtimer_list );
}
s32 edma_stress_test_start(s32 task_priority,s32 test_rate)
{
    s32 ret = 0;
    u32 index = 0;

    s32 chann_id = bsp_edma_channel_init(EDMA_MEMORY, 0, 0, 0);

    for (index=0;index<EDMA_HANDLE_NUM;index++)
    {
        g_edma_busstress_info.stDMATaskHandle[index].ulChIdx = chann_id;
    }
    hiedmac_trace("edma_stress: use axi 0x%x \n", MEM_FOR_EDMAC_BUSSTRESS,0,0,0,0,0);
    
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].u32SrcAddr = 0;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].u32DstAddr = 0;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].ulLength   = EDMA_TEST_LEN;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].ulChIdx    = chann_id;

#if 0
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_AXI_MEM].u32SrcAddr = 0;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_AXI_MEM].u32DstAddr = (unsigned int)EDMA_HANDLE_1_AXI_MEM_64_DST;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_AXI_MEM].ulLength   = EDMA_TEST_LEN;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_AXI_MEM].ulChIdx    = chann_id;

    
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_AXI_MEM].u32SrcAddr = (unsigned int)EDMA_HANDLE_2_AXI_MEM_64_SRC;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_AXI_MEM].u32DstAddr = (unsigned int)EDMA_HANDLE_2_AXI_MEM_64_DST;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_AXI_MEM].ulLength   = EDMA_TEST_LEN;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_AXI_MEM].ulChIdx    = chann_id;

    
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_DDR].u32SrcAddr = (unsigned int)EDMA_HANDLE_3_AXI_MEM_64_SRC;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_DDR].u32DstAddr = 0;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_DDR].ulLength   = EDMA_TEST_LEN;
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_DDR].ulChIdx    = chann_id;
 
	 g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_BBE16_DTCM].u32SrcAddr = 0;
	 g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_BBE16_DTCM].u32DstAddr = EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR;
	 g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_BBE16_DTCM].ulLength   = EDMA_TEST_LEN;
	 g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_BBE16_DTCM].ulChIdx	   = chann_id;
#endif
    
    set_test_switch_stat(EDMAC, TEST_RUN);

    /*创建控制发送速率的信号量*/
    /*sema_init(&(g_edma_busstress_info.edma_send_sem) , SEM_EMPTY);*/
    //g_edma_busstress_info.edma_send_sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    osl_sem_init(SEM_EMPTY,&g_edma_busstress_info.edma_send_sem);

    if (!g_edma_busstress_info.edma_send_sem)
    {
        hiedmac_trace("semBCreate gmac_send_sem fail.\n");
        return ERROR;
    }
    g_edma_busstress_info.edma_softtimer_list.func = ( softtimer_func )edma_timer_event;
    g_edma_busstress_info.edma_softtimer_list.para = 0;
    g_edma_busstress_info.edma_softtimer_list.timeout = test_rate;
    g_edma_busstress_info.edma_softtimer_list.wake_type = SOFTTIMER_NOWAKE;

    /*创建控制发送速率 的软timer*/
    
    if(bsp_softtimer_create(&g_edma_busstress_info.edma_softtimer_list))
    {
        hiedmac_trace("SOFTTIMER_CREATE_TIMER fail.\n");
        /*sema_delete(g_edma_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma_busstress_info.edma_send_sem);
        return ERROR;
    }

    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].u32SrcAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_DDR].u32DstAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
#if 0
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_AXI_MEM].u32SrcAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_AXI_MEM_TO_DDR].u32DstAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma_busstress_info.stDMATaskHandle[EDMA_MOVE_DDR_TO_BBE16_DTCM].u32SrcAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
#endif
    /*创建发包测试任务，收包驱动会自行做处理*/
    ret = osl_task_init ("edma2BusTask", task_priority, 20000, (OSL_TASK_FUNC)edma_stress_test_routine, 0,\
                                        &g_edma_busstress_info.edma_stress_test_task_id);

    if(OK!=ret)
    {
        hiedmac_trace("taskSpawn edmaBusTask fail.\n");
        /*sema_delete(g_edma_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma_busstress_info.edma_send_sem);
        bsp_softtimer_free(&g_edma_busstress_info.edma_softtimer_list);
    }
    else
    {
        bsp_softtimer_add( &g_edma_busstress_info.edma_softtimer_list );
    }
    return g_edma_busstress_info.edma_stress_test_task_id;
}

s32 edma_stress_test_stop()
{
    set_test_switch_stat(EDMAC, TEST_STOP);

    while(OK == osl_task_check(g_edma_busstress_info.edma_stress_test_task_id))
    {
        osl_task_delay(100);
    }

    if ((osl_sem_id) 0 != g_edma_busstress_info.edma_send_sem)
    {
        /*sema_delete(g_edma_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma_busstress_info.edma_send_sem);
    }


    bsp_softtimer_delete(&g_edma_busstress_info.edma_softtimer_list);
    bsp_softtimer_free(&g_edma_busstress_info.edma_softtimer_list);

    osl_cachedma_free((void*)g_edma_busstress_info.stDMATaskHandle[0].u32SrcAddr);
    osl_cachedma_free((void*)g_edma_busstress_info.stDMATaskHandle[0].u32DstAddr);
#if 0
    osl_cachedma_free((void*)g_edma_busstress_info.stDMATaskHandle[1].u32SrcAddr);
    osl_cachedma_free((void*)g_edma_busstress_info.stDMATaskHandle[3].u32DstAddr);
#endif
    return OK;
}



#if 0

//#define HI_EDMA_CH4_REGBASE_ADDR 0x90026000


struct edma_busstress_info g_edma2_busstress_info ;


s32 EDMA2_QueryCHNLState( u32 u32ChIdx )
{
    //s32 ret = -1;
    return (readl(HI_EDMA_CH4_REGBASE_ADDR+0x81c)&0x1);
}
s32 EDMA2_NormTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle)
{
    if(EDMA2_QueryCHNLState(0))
    {
        hiedmac_trace("channel %d is_idle failed in EDMA2_NormTaskLaunch",0 ,0,0,0,0,0);
    	return -1;
    }

    writel(EDMA_TEST_LEN, (HI_EDMA_CH4_REGBASE_ADDR+0x810));
    writel(pstDMAHandle->u32SrcAddr, (HI_EDMA_CH4_REGBASE_ADDR+0x814));
    writel(pstDMAHandle->u32DstAddr, (HI_EDMA_CH4_REGBASE_ADDR+0x818));
    writel(0xCFF33000, (HI_EDMA_CH4_REGBASE_ADDR+0x81C));
    writel(0xCFF33001, (HI_EDMA_CH4_REGBASE_ADDR+0x81C));
    return 0;


}

u32 g_edma2_bustest_count = 0;
s32 edma2_stress_test_routine()
{
    u32 count = 0;
    s32 s32ret = 0;
    u32 cur_idx = 0;

    while(get_test_switch_stat(EDMAC))
    {

        /*down(g_edma2_busstress_info.edma_send_sem);*/
        osl_sem_down(&g_edma2_busstress_info.edma_send_sem);

        if( 0 != EDMA2_QueryCHNLState(EDMA_CHANNEL_START))
        {
            continue;
        }

        if(count > 0)
        {
            if(0 != memcmp( (void*)g_edma2_busstress_info.stDMATaskHandle[cur_idx].u32DstAddr,\
                             (void*)g_edma2_busstress_info.stDMATaskHandle[cur_idx].u32SrcAddr,EDMA_TEST_LEN) )
            {
                hiedmac_trace("edma2 %d task,handle idx:%d,compare data fail.\n",count-1,cur_idx,0,0,0,0);
                return -1;
            }
        }

        cur_idx = count%EDMA_HANDLE_NUM;
        memset((void*)(void*)g_edma2_busstress_info.stDMATaskHandle[cur_idx].u32SrcAddr,cur_idx,EDMA_TEST_LEN);
        memset((void*)(void*)g_edma2_busstress_info.stDMATaskHandle[cur_idx].u32DstAddr,0xff,EDMA_TEST_LEN);
        s32ret = EDMA2_NormTaskLaunch( &(g_edma2_busstress_info.stDMATaskHandle[cur_idx]) );
        g_edma2_bustest_count++;
        if(s32ret != 0)
        {
            hiedmac_trace("EDMA2_NormTaskLaunch fail,ret:0x%x.\n",s32ret,0,0,0,0,0);
            continue;
        }

        count++;
    }

    return OK;
}

void edma2_timer_event(u32 param)
{
    if((osl_sem_id) 0 != g_edma2_busstress_info.edma_send_sem)
    {
        /*up(g_edma2_busstress_info.edma_send_sem);*/
        osl_sem_up(&g_edma2_busstress_info.edma_send_sem);
    }
    bsp_softtimer_add( &g_edma2_busstress_info.edma_softtimer_list );
}
s32 edma2_stress_test_start(s32 task_priority,s32 test_rate)
{
    s32 ret = 0;
    u32 index = 0;

    s32 chann_id = 0;/*bsp_edma_channel_init(EDMA_MEMORY, 0, 0, 0);*/

    for (index=0;index<EDMA_HANDLE_NUM;index++)
    {
        g_edma2_busstress_info.stDMATaskHandle[index].ulChIdx = chann_id;
    }
    hiedmac_trace("edma2_stress: use axi 0x%x \n", MEM_FOR_EDMAC2_BUSSTRESS,0,0,0,0,0);



    g_edma2_busstress_info.stDMATaskHandle[0].u32SrcAddr = 0;
    g_edma2_busstress_info.stDMATaskHandle[0].u32DstAddr = 0;
    g_edma2_busstress_info.stDMATaskHandle[0].ulLength   = EDMA_TEST_LEN;
    g_edma2_busstress_info.stDMATaskHandle[0].ulChIdx    = chann_id;

    
    g_edma2_busstress_info.stDMATaskHandle[1].u32SrcAddr = 0;
    g_edma2_busstress_info.stDMATaskHandle[1].u32DstAddr = EDMA2_HANDLE_1_AXI_MEM_64_DST;
    g_edma2_busstress_info.stDMATaskHandle[1].ulLength   = EDMA_TEST_LEN;
    g_edma2_busstress_info.stDMATaskHandle[1].ulChIdx    = chann_id;

    
    g_edma2_busstress_info.stDMATaskHandle[2].u32SrcAddr = EDMA2_HANDLE_2_AXI_MEM_64_SRC;
    g_edma2_busstress_info.stDMATaskHandle[2].u32DstAddr = EDMA2_HANDLE_2_AXI_MEM_64_DST;
    g_edma2_busstress_info.stDMATaskHandle[2].ulLength   = EDMA_TEST_LEN;
    g_edma2_busstress_info.stDMATaskHandle[2].ulChIdx    = chann_id;

    
    g_edma2_busstress_info.stDMATaskHandle[3].u32SrcAddr = EDMA2_HANDLE_3_AXI_MEM_64_SRC;
    g_edma2_busstress_info.stDMATaskHandle[3].u32DstAddr = 0;
    g_edma2_busstress_info.stDMATaskHandle[3].ulLength   = EDMA_TEST_LEN;
    g_edma2_busstress_info.stDMATaskHandle[3].ulChIdx    = chann_id;
 
    
    set_test_switch_stat(EDMAC, TEST_RUN);

    /*创建控制发送速率的信号量*/
    /*sema_init(&(g_edma2_busstress_info.edma_send_sem) , SEM_EMPTY);*/
    //g_edma2_busstress_info.edma_send_sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    osl_sem_init(SEM_EMPTY,&g_edma2_busstress_info.edma_send_sem);

    if (!g_edma2_busstress_info.edma_send_sem)
    {
        hiedmac_trace("semBCreate gmac_send_sem fail.\n");
        return ERROR;
    }
    g_edma2_busstress_info.edma_softtimer_list.func = ( softtimer_func )edma2_timer_event;
    g_edma2_busstress_info.edma_softtimer_list.para = 0;
    g_edma2_busstress_info.edma_softtimer_list.timeout = test_rate;
    g_edma2_busstress_info.edma_softtimer_list.wake_type =SOFTTIMER_NOWAKE;

    /*创建控制发送速率 的软timer*/
    if( bsp_softtimer_create(&g_edma2_busstress_info.edma_softtimer_list))
    {
        hiedmac_trace("SOFTTIMER_CREATE_TIMER fail.\n");
        /*sema_delete(g_edma2_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma2_busstress_info.edma_send_sem);
        return ERROR;
    }

    g_edma2_busstress_info.stDMATaskHandle[0].u32SrcAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma2_busstress_info.stDMATaskHandle[0].u32DstAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma2_busstress_info.stDMATaskHandle[1].u32SrcAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    g_edma2_busstress_info.stDMATaskHandle[3].u32DstAddr = (u32)osl_cachedma_malloc(EDMA_TEST_LEN);
    /*创建发包测试任务，收包驱动会自行做处理*/

    ret = osl_task_init ("edmaBusTask", task_priority, 20000, (OSL_TASK_FUNC)edma2_stress_test_routine, 0,\
                                       &g_edma2_busstress_info.edma_stress_test_task_id);

    
    if(OK!=ret)
    {
        hiedmac_trace("taskSpawn edma2BusTask fail.\n");
        /*sema_delete(g_edma2_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma2_busstress_info.edma_send_sem);
        bsp_softtimer_free(&g_edma2_busstress_info.edma_softtimer_list);
    }
    else
    {
        bsp_softtimer_add( &g_edma2_busstress_info.edma_softtimer_list );
    }
    return g_edma2_busstress_info.edma_stress_test_task_id;
}

s32 edma2_stress_test_stop()
{
    set_test_switch_stat(EDMAC, TEST_STOP);

    while(OK == osl_task_check(g_edma2_busstress_info.edma_stress_test_task_id))
    {
        osl_task_delay(100);
    }

    if ((osl_sem_id) 0 != g_edma2_busstress_info.edma_send_sem)
    {
        /*sema_delete(g_edma2_busstress_info.edma_send_sem);*/
        osl_sema_delete(&g_edma2_busstress_info.edma_send_sem);
    }


    bsp_softtimer_delete(&g_edma2_busstress_info.edma_softtimer_list);
    bsp_softtimer_free(&g_edma2_busstress_info.edma_softtimer_list);

    osl_cachedma_free((void*)g_edma2_busstress_info.stDMATaskHandle[0].u32SrcAddr);
    osl_cachedma_free((void*)g_edma2_busstress_info.stDMATaskHandle[0].u32DstAddr);
    osl_cachedma_free((void*)g_edma2_busstress_info.stDMATaskHandle[1].u32SrcAddr);
    osl_cachedma_free((void*)g_edma2_busstress_info.stDMATaskHandle[3].u32DstAddr);
    return OK;
}




#endif



u32 edma_lli_loop_src[16000] = {0};
u32 edma_lli_loop_des[16000] = {0};
struct edma_cb * edma_lli_loop_cb =0;
#include <osl_malloc.h>
#define EDMA_NONE 0
#define GFP_DMA EDMA_NONE
#define __GFP_WAIT EDMA_NONE

void * dma_alloc_coherent(void* none, u32 size, edma_addr_t *handle, u32 none2)
{
    void * memory;
    memory = osl_cachedma_malloc(size);
    *handle = (edma_addr_t)memory;
	return memory;
}

s32 edma_test_lli_loop(enum edma_req_id req )
{
    edma_addr_t  edma_addr    = 0;
    s32         ret_id       = 0;
    struct edma_cb *psttemp   = NULL;
    //enum edma_req_id req = EDMA_PWC_TDSP_TCM;

    /*build lli */
    edma_lli_loop_cb = (struct edma_cb *)dma_alloc_coherent(NULL,(2 * sizeof(struct edma_cb)),
                                                                   &edma_addr, GFP_DMA|__GFP_WAIT);

    if (NULL == edma_lli_loop_cb)
    {
        hiedmac_trace("LLI list init is failed!\n");
    	return EDMA_MEMORY_ALLOCATE_ERROR;
    }
    
    psttemp = edma_lli_loop_cb;
        //#define EDMA_BUSSTRESS_DDR_TO_DDR_SIZE  (64 * 1024 - 1)
        psttemp->lli = EDMA_SET_LLI(edma_addr + 0, 0);
        psttemp->config = EDMA_SET_CONFIG(req, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
        psttemp->src_addr = (unsigned int)edma_lli_loop_src;//osl_cachedma_malloc(EDMA_BUSSTRESS_DDR_TO_BBEDTCM_SIZE);//edma_lli_loop_src;
        psttemp->des_addr = (unsigned int)edma_lli_loop_des;//EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR;//edma_lli_loop_des;EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR
        psttemp->cnt0 = 4*16000;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;


    /*request the chan_id, */
    ret_id = bsp_edma_channel_init(req, NULL, 0, 0);
    if (ret_id < 0)
    {
        hiedmac_trace("-----------error ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /*获取首节点寄存器地址*/
    psttemp = bsp_edma_channel_get_lli_addr((u32)ret_id);
    if (NULL == psttemp)
    {
        hiedmac_trace("---bsp_edma_channel_get_lli_addr failed!\n\n");
        return EDMA_CHANNEL_INVALID;
    }
    hiedmac_trace("----------- edma_cb LLI = 0x%X!\n\n",(u32)psttemp);

    /*配置首节点寄存器*/
    psttemp->lli = edma_lli_loop_cb->lli;
    psttemp->config = edma_lli_loop_cb->config & 0xFFFFFFFE;
    psttemp->src_addr = edma_lli_loop_cb->src_addr;
    psttemp->des_addr = edma_lli_loop_cb->des_addr;
    psttemp->cnt0 = edma_lli_loop_cb->cnt0;
    psttemp->bindx = 0;
    psttemp->cindx = 0;
    psttemp->cnt1  = 0;

    if (bsp_edma_channel_lli_async_start((u32)ret_id))
    {
        hiedmac_trace("bsp_edma_channel_lli_start FAILED!\n\n");
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace("check state [bsp_edma_channel_is_idle %d] or addr 0x%x \n",ret_id,psttemp);
    return EDMA_SUCCESS;
}
s32 edma_test_lli_loop_tcm(enum edma_req_id req )
{
    edma_addr_t  edma_addr    = 0;
    s32         ret_id       = 0;
    struct edma_cb *psttemp   = NULL;
    //enum edma_req_id req = EDMA_PWC_TDSP_TCM;

    /*build lli */
    edma_lli_loop_cb = (struct edma_cb *)dma_alloc_coherent(NULL,(2 * sizeof(struct edma_cb)),
                                                                   &edma_addr, GFP_DMA|__GFP_WAIT);

    if (NULL == edma_lli_loop_cb)
    {
        hiedmac_trace("LLI list init is failed!\n");
    	return EDMA_MEMORY_ALLOCATE_ERROR;
    }

    psttemp = edma_lli_loop_cb;
        //#define EDMA_BUSSTRESS_DDR_TO_DDR_SIZE  (64 * 1024 - 1)
        psttemp->lli = EDMA_SET_LLI(edma_addr + 0, 0);
        psttemp->config = EDMA_SET_CONFIG(req, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
        psttemp->src_addr = (BBE16_LOCAL_MEM_SOCP_ADDR - 0x1000);//(unsigned int)edma_lli_loop_src;//osl_cachedma_malloc(EDMA_BUSSTRESS_DDR_TO_BBEDTCM_SIZE);//edma_lli_loop_src;
        psttemp->des_addr = (BBE16_LOCAL_MEM_SOCP_ADDR - 0x1000);//(unsigned int)edma_lli_loop_des;//EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR;//edma_lli_loop_des;EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR
        psttemp->cnt0 = 4*1000;//4*16000;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;


    /*request the chan_id, */
    ret_id = bsp_edma_channel_init(req, NULL, 0, 0);
    if (ret_id < 0)
    {
        hiedmac_trace("-----------error ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /*获取首节点寄存器地址*/
    psttemp = bsp_edma_channel_get_lli_addr((u32)ret_id);
    if (NULL == psttemp)
    {
        hiedmac_trace("---bsp_edma_channel_get_lli_addr failed!\n\n");
        return EDMA_CHANNEL_INVALID;
    }
    hiedmac_trace("----------- edma_cb LLI = 0x%X!\n\n",(u32)psttemp);

    /*配置首节点寄存器*/
    psttemp->lli = edma_lli_loop_cb->lli;
    psttemp->config = edma_lli_loop_cb->config & 0xFFFFFFFE;
    psttemp->src_addr = edma_lli_loop_cb->src_addr;
    psttemp->des_addr = edma_lli_loop_cb->des_addr;
    psttemp->cnt0 = edma_lli_loop_cb->cnt0;
    psttemp->bindx = 0;
    psttemp->cindx = 0;
    psttemp->cnt1  = 0;

    if (bsp_edma_channel_lli_async_start((u32)ret_id))
    {
        hiedmac_trace("bsp_edma_channel_lli_start FAILED!\n\n");
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace("check state [bsp_edma_channel_is_idle %d] or addr 0x%x \n",ret_id,psttemp);
    return EDMA_SUCCESS;
}




