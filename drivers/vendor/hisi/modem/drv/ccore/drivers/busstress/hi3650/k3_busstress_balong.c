#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include <osl_malloc.h>
#include "hi_base.h"
#include "mdrv.h"
#include "bsp_om.h"
#include "drv_comm.h"
#include "bsp_busstress.h"
#include <bsp_hardtimer.h>
#include <bsp_amon.h>
#include <bsp_edma.h>
#include "master.h"
#include <amon_balong.h>

BSP_BOOL g_bA9MemCpyTaskRun = BSP_FALSE;
BSP_U32 ccpu_busstress_count = 0;
BSP_S32 stress_test_rate = 2;
BSP_S32 cipher_stress_test_rate = 8;

/* 总线压测任务优先级 */
int g_busstress_test_edma_task_priority = 50;
int g_busstress_test_acc_task_priority = 50;
int g_busstress_test_cipher_task_priority = 50;
int g_busstress_test_kdf_task_priority = 50;
int g_busstress_test_mdm_a9_memcpy_task_priority = 49;
int g_busstress_test_get_a9_memcpy_bandwidth_task_priority = 10;
int g_busstress_test_ipf_task_priority = 49;
int g_busstress_test_gu_master_task_priority = 50;
int g_busstress_test_bbp_task_priority = 50;
int g_busstress_test_socp_ddr_to_ddr_task_priority = 50;
int g_busstress_test_socp_axi_mem_to_ddr_task_priority = 50;
int g_busstress_test_socp_bbe16dtcm_to_ddr_task_priority = 50;


extern BSP_S32 edma_stress_test_start(BSP_S32 task_priority, BSP_S32 test_rate);
extern BSP_S32 edma_stress_test_stop();
extern BSP_S32 acc_stress_test_start(BSP_S32 task_priority,BSP_S32 test_type,BSP_S32 test_rate);
extern BSP_S32 acc_stress_test_stop();
extern BSP_S32 cipher_stress_test_start(BSP_S32 task_priority,BSP_S32 test_rate);
extern BSP_S32 cipher_stress_test_stop();
extern BSP_S32 kdf_stress_test_start(BSP_S32 task_priority,BSP_S32 test_rate);
extern BSP_S32 kdf_stress_test_stop();
extern BSP_S32 ipf_dl_stress_test_start(BSP_S32 task_priority,BSP_S32 dtime);
extern BSP_S32 ipf_dl_stress_test_stop();
extern int for_hsuart_busstress_test_start(void);
extern int for_hsuart_busstress_test_stop(void);

extern int bsp_bbe_load_muti();
extern int bsp_bbe_run();
extern BSP_S32 SOCP_ST_ENCODE_DCORE_STRESS(int task_priority);
extern BSP_S32 SOCP_ST_ENCODE_STRESS_SRAM(int priority, u32 addr,u32 len);
extern BSP_U32 SOCP_ST_ENCODE_STRESS_TCM(int priority, u32 addr,u32 len);
extern void bsp_bbe_memcpy_stress_test_start(enum bbe16_move_type bbe16_move_type);
extern int bsp_bbe_memcpy_stress_test_result();

extern int gu_master_stress_test_start(int task_priority,int delayticks);
extern int gu_master_stress_test_stop();
extern void bbp_dma_stress_test(u32 bbp_addr,u32 len, u32 times,u32 edma_chn);
extern int bsp_bbe_stress_test_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3, UINT32 mailBody4, UINT16 msgID);
extern s32 edma_test_lli_loop(enum edma_req_id req);
extern int BSP_IPF_ST_210();
extern BSP_S32 SOCP_ST_BUSSTRESS_TEST(int priority,u32 addr,u32 len);

int busstress_test_show_cnt(void);


#define  printf(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_STRESS, "[stress test]: "fmt,  ##__VA_ARGS__))

enum a9_memcpy_type{
    A9_MEMCPY_AXI2AXI,             /* 0 */
	A9_MEMCPY_BBE_DTCM_2_BBE_DTCM, /* 1 */
	A9_MEMCPY_DDR_2_DDR,           /* 2 */
	A9_MEMCPY_TYPE_BUTTOM
};
struct a9_memcpy_tsk_param
{
    unsigned int src_addr;
	unsigned int dst_addr;
	int          size;
	int          delay_ticks;
	unsigned int ok_cnt;
	unsigned int fail_cnt;
};
struct a9_memcpy_tsk_param g_a9_memcpy_tsk_param[A9_MEMCPY_TYPE_BUTTOM] = {{0}};
struct a9_memcpy_tsk_param g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_TYPE_BUTTOM] = {{0}};


/*test process*/
BSP_S32 a9MemcpyTaskFunc(BSP_S32 s32TestSence,BSP_S32 s32DelayVal)
{
	BSP_U32 u32Src = 0;
	BSP_U32 u32Dst = 0;
	BSP_S32 s32Size = 0;
	BSP_U32 u32Cnt = 0;

	switch(s32TestSence)
	{
	case DDR:
		s32Size = A9_DATA_CACHE_SIZE;
		u32Src = (BSP_U32)malloc(s32Size);
		if(0 == u32Src)
		{
			printf("malloc %s buffer fail.\n","src");
			return ERROR;
		}

		u32Dst = (BSP_U32)malloc(s32Size);
		if(0 == u32Dst)
		{
			printf("malloc %s buffer fail.\n","dst");
			free((void*)u32Src);
			return ERROR;
		}
		break;
	case AXIMEM:
		s32Size = AXI_MEM_SIZE_FOR_A9;
		u32Src = (BSP_U32)alloc(s32Size);
		if(0 == u32Src)
		{
			printf("malloc %s buffer fail.\n","src");
			return ERROR;
		}

		u32Dst = (BSP_U32)alloc(s32Size);
		if(0 == u32Dst)
		{
			printf("malloc %s buffer fail.\n","dst");
			return ERROR;
		}
		break;
	default:
		printf("s32TestSence invalid.\n");
		return ERROR;
	}

	while(g_bA9MemCpyTaskRun)
	{
		memcpyTestProcess((void*)u32Src, (void*)u32Dst,s32Size);
		if(DDR == s32TestSence)
		{
			(BSP_VOID)osl_cache_flush(OSL_DATA_CACHE, (BSP_VOID *)u32Dst, s32Size);
		}
		u32Cnt++;
		if(0 == (u32Cnt%5))
		{
			osl_task_delay(s32DelayVal);
		}
	}

	if(DDR == s32TestSence)
	{
		free((void*)u32Src);
		free((void*)u32Dst);
	}
	else	{}

	return OK;
}
BSP_S32 g_A9MemCpy_TaskPriority = VX_DEFAULT_PRIORITY;
OSL_TASK_ID g_A9taskid;
BSP_S32 a9_mem_stress_test_start(BSP_S32 s32TestSence,BSP_S32 s32DelayValue)
{
	char        taskName[30] = {0};
	BSP_S32     s32Ret = 0;
    BSP_S32     s32LocalDelayVal = s32DelayValue;
	int         para[2] = {s32TestSence,s32DelayValue};

	if(0 == s32LocalDelayVal)
	{
		s32LocalDelayVal = 1;
	}

	sprintf(taskName,"a9S%dMemcpyTask",s32TestSence);
	g_bA9MemCpyTaskRun = BSP_TRUE;
	s32Ret = osl_task_init(taskName,g_A9MemCpy_TaskPriority,2000,(OSL_TASK_FUNC)a9MemcpyTaskFunc,(void *)para,&g_A9taskid);
	if(ERROR == s32Ret)
	{
		printf("taskSpawn %s fail.\n","a9S1MemcpyTask");
		return ERROR;
	}

	return OK;
}

BSP_S32 a9_mem_stress_test_stop(BSP_S32 s32TestSence)
{
	char taskName[30] = {0};

	sprintf(taskName,"a9S%dMemcpyTask",s32TestSence);
	g_bA9MemCpyTaskRun = BSP_FALSE;

	while(OK == osl_task_check(g_A9taskid))
	{
		osl_task_delay(500);
	}
	printf("delete %s OK.\n","a9S1MemcpyTask");
	return OK;
}

/*For A9 Access HIFI Local Mem and bbe16 Local Mem*/
BSP_BOOL g_bA9MemCpyTaskRunExt = BSP_TRUE;
OSL_TASK_ID g_bA9taskid;
BSP_S32 a9MemcpyTestFuncExt(void *para)
{
	BSP_U32 u32Cnt = 0;
    struct a9_memcpy_tsk_param *pstru_a9_memcpy_tsk_param = (struct a9_memcpy_tsk_param *)para;
	BSP_U32 u32Src = pstru_a9_memcpy_tsk_param->src_addr;
	BSP_U32 u32Dst = pstru_a9_memcpy_tsk_param->dst_addr;
	BSP_S32 s32Size = pstru_a9_memcpy_tsk_param->size;
//	BSP_S32 s32DelayVal = pstru_a9_memcpy_tsk_param->delay_ticks;


	while(g_bA9MemCpyTaskRunExt)
	{
		if(0 != memcpyTestProcess((void*)u32Src, (void*)u32Dst, s32Size))
		{
			//printf("u32Src:0x%08x,u32Dst:0x%08x\n",u32Src,u32Dst);
			pstru_a9_memcpy_tsk_param->fail_cnt++;
			//break;
		}

		pstru_a9_memcpy_tsk_param->ok_cnt++;

		/* cache flush放到memcpyTestProcess里做 */
		//(BSP_VOID)osl_cache_flush(OSL_DATA_CACHE, (BSP_VOID *)u32Src, s32Size);
		//(BSP_VOID)osl_cache_flush(OSL_DATA_CACHE, (BSP_VOID *)u32Dst, s32Size);
		u32Cnt++;
		/* 为提高压力，去掉延时 */
		#if 1
		if(0 == (u32Cnt % 5))
		{
			osl_task_delay(1);
		}
		#endif

	}
	return BSP_OK;
}

BSP_S32 a9MemcpyTaskSpawnExt(BSP_U32 u32Src,BSP_U32 u32Dst,BSP_S32 s32Size,BSP_S32 s32DelayValue)
{
	char taskName[30] = {0};
	BSP_S32 s32Ret = 0;
    BSP_S32 s32LocalDelayVal = s32DelayValue;
	void *para = NULL;
	char *str_memcpy_type = NULL;

	if(0 == s32LocalDelayVal)
	{
		s32LocalDelayVal = 1;
	}

    if (((unsigned int)AXI_MEM_FOR_A9_CCORE_SRC_ADDR) == u32Src)  /* axi_mem to axi_mem */
	{
	    g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].src_addr = u32Src;
	    g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].dst_addr = u32Dst;
	    g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].size = s32Size;
	    g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].delay_ticks = s32DelayValue;
		para = &g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI];
		str_memcpy_type = "[a9 aximem to aximem]";
	}
	else if (((unsigned int)A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SRC_ADDR) == u32Src)  /* bbe16 dtcm to bbe16 dtcm */
	{
		g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].src_addr = u32Src;
		g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].dst_addr = u32Dst;
		g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].size = s32Size;
		g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].delay_ticks = s32DelayValue;
		para = &g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM];
		str_memcpy_type = "[a9 bbe16 dtcm to bbe16 dtcm]";
	}
	else  /* ddr to ddr */
	{
		g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].src_addr = u32Src;
		g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].dst_addr = u32Dst;
		g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].size = s32Size;
		g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].delay_ticks = s32DelayValue;
		para = &g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR];
		str_memcpy_type = "[a9 ddr to ddr]";
	}

	sprintf(taskName,"a9MemcpyTask%x",u32Src);
	g_bA9MemCpyTaskRunExt = BSP_TRUE;
	s32Ret = osl_task_init(taskName,g_busstress_test_mdm_a9_memcpy_task_priority,2000,(OSL_TASK_FUNC)a9MemcpyTestFuncExt,(void *)para,&g_bA9taskid);
	if(ERROR == s32Ret)
	{
		printf("%s taskSpawn %s fail.\n", str_memcpy_type, taskName);
		return ERROR;
	}

	printf("%s taskSpawn %s ok\n", str_memcpy_type, taskName);

	return OK;
}

BSP_S32 a9MemcpyTaskDeleteExt(BSP_U32 u32Src)
{
	char taskName[30] = {0};

	sprintf(taskName,"a9MemcpyTask%x",u32Src);
	g_bA9MemCpyTaskRunExt = BSP_FALSE;

	while(OK == osl_task_check(g_bA9taskid))
	{
		osl_task_delay(500);
	}
	printf("delete %s OK.\n",taskName);
	return OK;
}

void *g_stress_src_addr = NULL;
void *g_stress_dst_addr = NULL;
/* 搬移1k */
BSP_S32 a9_mem_stress_test_start_ddr2ddr(BSP_S32 s32DelayValue)
{
    /* 申请不可cache内存，避免cache操作 */
	g_stress_src_addr = osl_cachedma_malloc(DDR_MEM_SIZE_FOR_A9);//malloc(DDR_MEM_SIZE_FOR_A9);
	if(NULL == g_stress_src_addr)
	{
		return ERROR;
	}
	/* 申请不可cache内存，避免cache操作 */
	g_stress_dst_addr = osl_cachedma_malloc(DDR_MEM_SIZE_FOR_A9);//malloc(DDR_MEM_SIZE_FOR_A9);
	if(NULL == g_stress_dst_addr)
	{
        free(g_stress_src_addr);
        g_stress_src_addr = NULL;
		return ERROR;
	}

	a9MemcpyTaskSpawnExt((BSP_U32)g_stress_src_addr, (BSP_U32)g_stress_dst_addr,DDR_MEM_SIZE_FOR_A9,s32DelayValue);
	return OK;
}

BSP_U32 a9_mem_stress_test_stop_use_ddr()
{
    if(g_stress_src_addr)
    {
        a9MemcpyTaskDeleteExt((BSP_U32)g_stress_src_addr);
        free(g_stress_src_addr);
        g_stress_src_addr = NULL;
    }

    if(g_stress_dst_addr)
    {
        free(g_stress_dst_addr);
        g_stress_dst_addr = NULL;
    }

    return OK;
}

/* 搬移1k */
BSP_S32 a9_mem_stress_test_start_bbe16dtcm2bbe16dtcm(BSP_S32 s32DelayValue)
{
	a9MemcpyTaskSpawnExt((BSP_U32)A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SRC_ADDR,
		                 (BSP_U32)(A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SRC_ADDR + A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SIZE ),
		                 (BSP_U32)A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SIZE, s32DelayValue);
	return OK;
}
BSP_S32 a9_mem_stress_test_stop_use_bbe16()
{
	a9MemcpyTaskDeleteExt(BBE_TCM_ADDR);
	return OK;
}
#if 0
BSP_S32 a9_mem_stress_test_start_use_hifi(BSP_S32 s32DelayValue)
{
	BSP_S32 reg = 0x1C0000;
	/*?a?′??*/
 	writel(reg, 0x90000070);
	a9MemcpyTaskSpawnExt(HIFI_TCM_ADDR,HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR,HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE,s32DelayValue);
	return OK;
}
BSP_S32 a9_mem_stress_test_stop_use_hifi()
{
	a9MemcpyTaskDeleteExt(HIFI_TCM_ADDR);
	return OK;
}
#endif
#if 0
BSP_S32 a9_mem_stress_test_start_use_m3(BSP_S32 s32DelayValue)
{
	a9MemcpyTaskSpawnExt(M3_LOCAL_MEM_SRC_FOR_A9_MCORE,M3_LOCAL_MEM_DST_FOR_A9_MCORE,M3_LOCAL_MEM_FOR_MEMCPY_SIZE,s32DelayValue);
	return OK;
}
BSP_S32 a9_mem_stress_test_stop_use_m3()
{
	a9MemcpyTaskDeleteExt(M3_LOCAL_MEM_SRC_FOR_A9_MCORE);
	return OK;
}
#endif

/* 搬移10k */
BSP_S32 a9_mem_stress_test_start_aximem2aximem(BSP_S32 s32DelayValue)
{
	a9MemcpyTaskSpawnExt((BSP_U32)AXI_MEM_FOR_A9_CCORE_SRC_ADDR, 
		                 (BSP_U32)AXI_MEM_FOR_A9_CCORE_DST_ADDR, 
		                 AXI_MEM_FOR_A9_CCORE_SIZE, 
		                 s32DelayValue);
	return OK;
}

BSP_S32 a9_mem_stress_test_start_use_aximem64_count()
{
	printf("ccpu busstress count: %u", ccpu_busstress_count);
	return OK;
}

BSP_S32 a9_mem_stress_test_stop_use_aximem64()
{
	a9MemcpyTaskDeleteExt((BSP_U32)AXI_MEM_FOR_A9_CCORE_SRC_ADDR);
	return OK;
}

unsigned int g_busstress_test_start_time_stamp = 0;
unsigned int g_busstress_test_now_time_stamp = 0;

int g_busstress_test_amon_info_tsk_delay_ticks = 0;

enum amon_res_id{
	AMON_RES0_BBE16_1,
	AMON_RES1_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1,
	AMON_RES2_EDMA,
	AMON_RES3_PERI_MST,
	AMON_RES4_IPF,
	AMON_RES5_AP_MST,
	AMON_RES6_MCPU_M0,
	AMON_RES7_MCPU_M1,
	AMON_RES_ID_BUTTOM
};

const char *g_res_str[AXI_MAX_CONFIG_ID] = {
	"res0:BBE16_1----------------------",
	"res1:LTEBBP LTEBBP_1 GUBBP_MST_1--",
	"res2:EDMA-------------------------",
	#ifdef RES3_FOR_PERI_MST
	"res3:PERI_MST---------------------",
	#else
	"res3:CIPHER-----------------------",
	#endif
	"res4:IPF--------------------------",
	"res5:AP_MST-----------------------",
	"res6:MCPU_M0----------------------",
	"res7:MCPU_M1----------------------"
};

const char *g_port_res_map_str[6] = {
	"PORT0:BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1\n",
    #ifdef RES3_FOR_PERI_MST
	"PORT1:PERI_MST\n",
	#else
	"PORT1:CIPHER\n",
	#endif
	"PORT2:AP_MST\n",
	"PORT3:MCPU_M0\n",
	"PORT4:reserved\n",
	"PORT5:MCPU_M1:TO_DDR_NOTHING_TO_DO_WITH_AXI\n"
};

/* PORT4保留不用，PORT5用于DDR，不走AXI总线，不关注 */
enum port_we_care_with_axi{
	PORT0_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1,
	PORT1_PERI_MST,
	PORT2_AP_MST,
	PORT3_MCPU_M0,
	PORT4_RESERVED,
	PORT5_L2,
	PORT_BUTTOM
};

/* amon监控信息显示最大次数 */
#define AMON_INFO_SHOW_MAX_CNT    (1500)

/* 各组资源的读写利用率，百分比 */
float g_res_rd_usage_times[AMON_INFO_SHOW_MAX_CNT][AMON_RES_ID_BUTTOM] = {{0.00000}};
float g_res_wr_usage_times[AMON_INFO_SHOW_MAX_CNT][AMON_RES_ID_BUTTOM] = {{0.00000}};

/* 各组资源的读写带宽 Mbps */
float g_res_rd_band_width[AMON_INFO_SHOW_MAX_CNT][AMON_RES_ID_BUTTOM] = {{0.00000}};
float g_res_wr_band_width[AMON_INFO_SHOW_MAX_CNT][AMON_RES_ID_BUTTOM] = {{0.00000}};

/* 各PORT的读写利用率，百分比，一个PORT可能包含多组资源 */
float g_port_rd_usage_times[AMON_INFO_SHOW_MAX_CNT][PORT_BUTTOM] = {{0.00000}};
float g_port_wr_usage_times[AMON_INFO_SHOW_MAX_CNT][PORT_BUTTOM] = {{0.00000}};

/* 各PORT的读写带宽 Mbps */
float g_port_rd_band_width[AMON_INFO_SHOW_MAX_CNT][PORT_BUTTOM] = {{0.00000}};
float g_port_wr_band_width[AMON_INFO_SHOW_MAX_CNT][PORT_BUTTOM] = {{0.00000}};

unsigned int g_amon_info_show_cnt = 0;

#define EFFECTIVE_COEFFICIENT_ON_PORTING   (0.6)  /* porting上有效带宽按60%计算 */

/* AXI总线各PORT间是可以并行的，因此统计每个PORT的利用率才有意义 */
void busstress_test_amon_info_task(void *para)
{
    int local_tsk_delay_ticks = *((int*)para);
	amon_count_stru busstress_test_amon_cnt;
	float           period_seconds = 0.0;
	int ret= 0;
	int i = 0;
	u64 port_rd_access[6] = {0};
	u64 port_wr_access[6] = {0};
	u64 res_rd_access[AMON_RES_ID_BUTTOM] = {0};
	u64 res_wr_access[AMON_RES_ID_BUTTOM] = {0};


	for (;;)
	{
	    osl_task_delay(local_tsk_delay_ticks);

	    SRE_Printf("************busstress test amon info  cnt = %d************************************\n", g_amon_info_show_cnt);
		/* 首先清零 */
		for (i = 0; i < 6; i++)
		{
			port_rd_access[i]  = 0;
			port_wr_access[i] = 0;
		}
		for (i = 0; i < AMON_RES_ID_BUTTOM; i++)
		{
			res_rd_access[i] = 0;
			res_wr_access[i] = 0;
		}

		ret = (int)amon_get_info(&busstress_test_amon_cnt);
		if (0 != ret)
		{
		    SRE_Printf("amon_get_info err ret=%d, please inspiring the next time\n", ret);
			continue ;
		}

        period_seconds =  (float)(((double)busstress_test_amon_cnt.monitor_time_delta) / STRESS_TIME_FREQ);

        #if 0
		printf("high_32 = 0x%08x low_32 = 0x%08x\n", (u32)((busstress_test_amon_cnt.global_access_count) >> 32),
			                                         (u32)(busstress_test_amon_cnt.global_access_count));
		#endif

        /* 打印各资源本次监控中的数据量:字节数，高32bit和低32bit分别显示 */
		SRE_Printf("             resource               read_high  read_low   write_high write_low\n");
        for (i = 0; i < AXI_MAX_CONFIG_ID; i++)
    	{
			SRE_Printf("%s  0x%08x 0x%08x 0x%08x 0x%08x\n", g_res_str[i],
				              busstress_test_amon_cnt.soc_read_count[i].hig_count, busstress_test_amon_cnt.soc_read_count[i].low_count,
				              busstress_test_amon_cnt.soc_write_count[i].hig_count, busstress_test_amon_cnt.soc_write_count[i].low_count);
    	}
		/* 得到本次各资源的读写利用率及带宽 */
		for (i = 0; i < AMON_RES_ID_BUTTOM; i++)
		{
		    res_rd_access[i]= (((u64)(busstress_test_amon_cnt.soc_read_count[i].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[i].low_count));
		    res_wr_access[i]= (((u64)(busstress_test_amon_cnt.soc_write_count[i].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[i].low_count));

			g_res_rd_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)res_rd_access[i] / (double)period_seconds / 1024 / 1024 * 8);
			//SRE_Printf("%d=======================%8.3fMbps\n", i, g_res_rd_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
			g_res_rd_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)res_rd_access[i] / ((double)busstress_test_amon_cnt.global_access_count * EFFECTIVE_COEFFICIENT_ON_PORTING) * 100);
			//SRE_Printf("%d=======================%6.3f%%\n", i, g_res_rd_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
			g_res_wr_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)res_wr_access[i] / (double)period_seconds / 1024 / 1024 * 8);
			//SRE_Printf("%d=======================%8.3fMbps\n", i, g_res_wr_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
			g_res_wr_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)res_wr_access[i] / ((double)busstress_test_amon_cnt.global_access_count * EFFECTIVE_COEFFICIENT_ON_PORTING) * 100);
			//SRE_Printf("%d=======================%6.3f%%\n", i, g_res_wr_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
		}
		SRE_Printf("******************** 50MHz*64bit*0.6 in theory on porting\n");
		/* 打印本次的各资源的读写带宽及利用率 */
		SRE_Printf("****time%d\n", g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT);
		SRE_Printf("**read\n");
		SRE_Printf("        rd_band_width   rd_util_ratio\n");
		for (i = 0; i < AMON_RES_ID_BUTTOM; i++)
		{
		    SRE_Printf("res%d   %8.3fMbps     %6.3f%%\n", i,
					g_res_rd_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i],
					g_res_rd_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
		}
		SRE_Printf("**write\n");
		SRE_Printf("       wr_band_width   wr_util_ratio\n");
		for (i = 0; i < AMON_RES_ID_BUTTOM; i++)
		{
		    SRE_Printf("res%d   %8.3fMbps     %6.3f%%\n", i,
					g_res_wr_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i],
					g_res_wr_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);

		}



        /* port0=res0+res1*/
		port_rd_access[0] = (((u64)(busstress_test_amon_cnt.soc_read_count[0].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[0].low_count)) +
		                      (((u64)(busstress_test_amon_cnt.soc_read_count[1].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[1].low_count));
		port_wr_access[0] = (((u64)(busstress_test_amon_cnt.soc_write_count[0].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[0].low_count)) +
		                      (((u64)(busstress_test_amon_cnt.soc_write_count[1].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[1].low_count));

		/* port1=res3*/
		port_rd_access[1] = ((u64)(busstress_test_amon_cnt.soc_read_count[3].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[3].low_count);
		port_wr_access[1] = ((u64)(busstress_test_amon_cnt.soc_write_count[3].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[3].low_count);

		/* port2=res5*/
		port_rd_access[2] = ((u64)(busstress_test_amon_cnt.soc_read_count[5].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[5].low_count);
		port_wr_access[2] = ((u64)(busstress_test_amon_cnt.soc_write_count[5].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[5].low_count);

		/* port3=res6*/
		port_rd_access[3] = ((u64)(busstress_test_amon_cnt.soc_read_count[6].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[6].low_count);
		port_wr_access[3] = ((u64)(busstress_test_amon_cnt.soc_write_count[6].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[6].low_count);

		/* port4 保留 */

		/* port5=res7 L2 MDM_A9访问DDR */
		port_rd_access[5] = ((u64)(busstress_test_amon_cnt.soc_read_count[7].hig_count) << 32) | (busstress_test_amon_cnt.soc_read_count[7].low_count);
		port_wr_access[5] = ((u64)(busstress_test_amon_cnt.soc_write_count[7].hig_count) << 32) | (busstress_test_amon_cnt.soc_write_count[7].low_count);



        for (i = PORT0_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1; i < PORT_BUTTOM; i++)
    	{
    	    if (PORT4_RESERVED == i)
	    	{
	    	    continue ;
	    	}

			/* 本段时间内各端口的带宽及利用率 */
			g_port_rd_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)port_rd_access[i] / (double)period_seconds / 1024 / 1024 * 8);
			g_port_rd_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)port_rd_access[i] / ((double)busstress_test_amon_cnt.global_access_count * EFFECTIVE_COEFFICIENT_ON_PORTING) * 100);
			g_port_wr_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)port_wr_access[i] / (double)period_seconds / 1024 / 1024 * 8);
			g_port_wr_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i] = (float)((double)port_wr_access[i] / ((double)busstress_test_amon_cnt.global_access_count * EFFECTIVE_COEFFICIENT_ON_PORTING) * 100);
		}

	     SRE_Printf("********************\n");
        /* 打印各端口监控的是什么 */
		for (i = 0; i < PORT_BUTTOM; i++)
		{
	         SRE_Printf("%s", g_port_res_map_str[i]);
		}

		/* 打印本次各PORT的带宽及利用率 */
		SRE_Printf("****time%d\n", g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT);
		SRE_Printf("**read\n");
		SRE_Printf("        rd_band_width	rd_util_ratio\n");
		for (i = 0; i < PORT_BUTTOM; i++)
		{
    	    if (PORT4_RESERVED == i)
	    	{
	    	    continue ;
	    	}
		    SRE_Printf("PORT%d    %8.3fMbps      %6.3f%%\n", i,
					g_port_rd_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i],
					g_port_rd_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);
		}

		SRE_Printf("**write\n");
		SRE_Printf("        wr_band_width	  wr_util_ratio\n");
		for (i = 0; i < PORT_BUTTOM; i++)
		{
    	    if (PORT4_RESERVED == i)
	    	{
	    	    continue ;
	    	}
		    SRE_Printf("PORT%d    %8.3fMbps      %6.3f%%\n", i,
					g_port_wr_band_width[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i],
					g_port_wr_usage_times[g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT][i]);

		}



        /* 打印各搬移的次数信息 */
		//(void)busstress_test_show_cnt();

		SRE_Printf("**********************amon info end cnt = %d********************************\n", g_amon_info_show_cnt);

		g_amon_info_show_cnt++;


	}


    return ;
}

/* 打印资源读写利用率及端口读写利用率历史数据 */
int busstress_test_show_usage(void)
{
    int i = 0;

	SRE_Printf("\n\n****************************************************************************\n");
	/* 资源利用率 */
	SRE_Printf("resource usage\n");
	SRE_Printf("time 0_rd    0_wr    1_rd    1_wr    2_rd    2_wr    3_rd    3_wr    4_rd    4_wr    5_rd    5_wr    6_rd    6_wr    7_rd    7_wr\n");
	for (i = 0; i < g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT; i++)
	{
		SRE_Printf("%04d %.3f%%  %.3f%%  %.3f%%  %.3f%%  ", i,
							g_res_rd_usage_times[i][AMON_RES0_BBE16_1],
							g_res_wr_usage_times[i][AMON_RES0_BBE16_1],
							g_res_rd_usage_times[i][AMON_RES1_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1],
							g_res_wr_usage_times[i][AMON_RES1_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1]);
		SRE_Printf("%.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%  ",
							g_res_rd_usage_times[i][AMON_RES2_EDMA],
							g_res_wr_usage_times[i][AMON_RES2_EDMA],
							g_res_rd_usage_times[i][AMON_RES3_PERI_MST],
							g_res_wr_usage_times[i][AMON_RES3_PERI_MST],
							g_res_rd_usage_times[i][AMON_RES4_IPF],
							g_res_wr_usage_times[i][AMON_RES4_IPF]);
		SRE_Printf("%.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%\n",
							g_res_rd_usage_times[i][AMON_RES5_AP_MST],
							g_res_wr_usage_times[i][AMON_RES5_AP_MST],
							g_res_rd_usage_times[i][AMON_RES6_MCPU_M0],
							g_res_wr_usage_times[i][AMON_RES6_MCPU_M0],
							g_res_rd_usage_times[i][AMON_RES7_MCPU_M1],
							g_res_wr_usage_times[i][AMON_RES7_MCPU_M1]);
	}

	SRE_Printf("********************\n");
	/* 端口利用率 */
	SRE_Printf("port usage\n");
	SRE_Printf("time 0_rd    0_wr    1_rd    1_wr    2_rd    2_wr    3_rd    3_wr    5_rd    5_wr\n");
	for (i = 0; i < g_amon_info_show_cnt % AMON_INFO_SHOW_MAX_CNT; i++)
	{
		SRE_Printf("%04d %.3f%%  %.3f%%  %.3f%%  %.3f%%  ", i,
							g_port_rd_usage_times[i][PORT0_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1],
							g_port_wr_usage_times[i][PORT0_BBE16_1_LTEBBP_LTEBBP_1_GUBBP_MST_1],
							g_port_rd_usage_times[i][PORT1_PERI_MST],
							g_port_wr_usage_times[i][PORT1_PERI_MST]);

		SRE_Printf("%.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%  %.3f%%\n",
							g_port_rd_usage_times[i][PORT2_AP_MST],
							g_port_wr_usage_times[i][PORT2_AP_MST],
							g_port_rd_usage_times[i][PORT3_MCPU_M0],
							g_port_wr_usage_times[i][PORT3_MCPU_M0],
							g_port_rd_usage_times[i][PORT5_L2],
							g_port_wr_usage_times[i][PORT5_L2]);


	}

	SRE_Printf("****************************************************************************\n\n\n");
    return 0;
}



OSL_TASK_ID g_amon_info_tsk_id;

int busstress_test_start_monitor(int amon_info_tsk_priority)
{
	int ret = 0;
	amon_config_stru busstress_test_amon_cfg = {0};
	axi_config_enum_uint32 bustress_test_axi_cfg_enum = 0;
	/*使能SOC监控*/
	busstress_test_amon_cfg.en_flag = AMON_SOC_MASK;

    /* PORT0:资源0+资源1 */
	/* res0:监控BBE16_1*/
	busstress_test_amon_cfg.soc_config[0].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[0].port = 0;
	busstress_test_amon_cfg.soc_config[0].master_id = 0x800F8060;
    /* res1:监控LTEBBP LTEBBP_1 GUBBP_MST_1  */
	busstress_test_amon_cfg.soc_config[1].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[1].port = 0;
	busstress_test_amon_cfg.soc_config[1].master_id = 0x803F8080;
    /* res2:监控EDMA*/
	busstress_test_amon_cfg.soc_config[2].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[2].port = 1;
	busstress_test_amon_cfg.soc_config[2].master_id = 0x80078010;

    /* PORT1:资源3 */
	#ifdef 	RES3_FOR_PERI_MST
	/* res3:监控peri_mst,包括UICC/EDMA/CIPHER/IPF/UPACC/CICOM0/CICOM1*/
	busstress_test_amon_cfg.soc_config[3].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[3].port = 1;
	busstress_test_amon_cfg.soc_config[3].master_id = 0x0;
	#else
	/* res3:监控cipher */
	busstress_test_amon_cfg.soc_config[3].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[3].port = 1;
	busstress_test_amon_cfg.soc_config[3].master_id = 0x80078020;
	#endif

    /* res4:监控IPF*/
	busstress_test_amon_cfg.soc_config[4].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[4].port = 1;
	busstress_test_amon_cfg.soc_config[4].master_id = 0x80078030;

    /* PORT2:资源5 */
	/* res5:监控AP_MST*/
	busstress_test_amon_cfg.soc_config[5].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[5].port = 2;
	busstress_test_amon_cfg.soc_config[5].master_id = 0x0;

    /* PORT3:资源6 */
	/* res6:监控MCPU_M0(MCPU)*/
	busstress_test_amon_cfg.soc_config[6].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[6].port = 3;
	busstress_test_amon_cfg.soc_config[6].master_id = 0x0;

    /* PORT5:资源7 */
	/* res7:监控MCPU_M1,访问DDR，不能算在AXI GLOBAL里*/
	busstress_test_amon_cfg.soc_config[7].opt_type = (AMON_OPT_READ | AMON_OPT_WRITE);
	busstress_test_amon_cfg.soc_config[7].port = 5;
	busstress_test_amon_cfg.soc_config[7].master_id = 0x0;

	ret = (int)amon_set_config(busstress_test_amon_cfg);
	if (0 != ret)
	{
	    printf("amon_set_config err ret=%d\n", ret);
		return -1;
	}

    /* 启动 */
	bustress_test_axi_cfg_enum = AXI_SOC_CONFIG;
    ret = amon_start(bustress_test_axi_cfg_enum);
	if (0 != ret)
	{
        printf("amon_start err ret=%d\n", ret);
		return -1;
	}

	g_busstress_test_amon_info_tsk_delay_ticks = 6000;

	/* 起任务查看信息 */
	ret = osl_task_init((char*)"amon_info_tsk", amon_info_tsk_priority, 2000, (OSL_TASK_FUNC)busstress_test_amon_info_task,
	                    (void *)&g_busstress_test_amon_info_tsk_delay_ticks, &g_amon_info_tsk_id);
	if (0 != ret)
	{
	    printf("amon_info_tsk osl_task_init err ret=%d\n", ret);
		return -1;
	}

    return 0;
}


struct bbp_busstress_test_task_para
{
    unsigned int bbp_addr;
	unsigned int len;
	unsigned int edma_chn;
};

struct bbp_busstress_test_task_para g_bbp_busstress_test_task_para = {0};
OSL_TASK_ID g_bbp_busstress_test_task_id;

void bbp_busstress_test_task(void *para)
{
    struct bbp_busstress_test_task_para *bbp_para = (struct bbp_busstress_test_task_para *)para;
    unsigned int bbp_addr = bbp_para->bbp_addr;
    unsigned int len = bbp_para->len;
    unsigned int edma_chn = bbp_para->edma_chn;

	bbp_dma_stress_test(bbp_addr, len, 0, edma_chn);  /* 内有无限循环 */

    return ;
}

#define BBP_BUSSTRESS_TEST_BBP_TRANS_SIZE  (1 * 1024)
int bbp_busstress_test_spawn_task(int priority)
{
    int ret = 0;

    g_bbp_busstress_test_task_para.bbp_addr = 0xE1000800;
	g_bbp_busstress_test_task_para.len = BBP_BUSSTRESS_TEST_BBP_TRANS_SIZE;
	g_bbp_busstress_test_task_para.edma_chn = 8;

	ret = osl_task_init((char*)"bbp_bus_tsk", priority, 2000, (OSL_TASK_FUNC)bbp_busstress_test_task,
	                    (void *)&g_bbp_busstress_test_task_para, &g_bbp_busstress_test_task_id);
	if (0 != ret)
	{
	    printf("amon_info_tsk osl_task_init err ret=%d\n", ret);
		return -1;
	}



    return 0;
}

enum busstress_module_no{
	BUSSTRESS_TEST_BBE16,                      /* 0 */
	BUSSTRESS_TEST_ACC,                        /* 1 */
	BUSSTRESS_TEST_CIPHER,                     /* 2 */
	BUSSTRESS_TEST_KDF,                        /* 3 */
	BUSSTRESS_TEST_EDMA,                       /* 4 */
	BUSSTRESS_TEST_MDM_A9_AXIMEM2AXIMEM,       /* 5 */
	BUSSTRESS_TEST_MDM_A9_BBE16DTCM2BBE16DTCM, /* 6 */
	BUSSTRESS_TEST_MDM_A9_DDR2DDR,             /* 7 */
	BUSSTRESS_TEST_IPF,                        /* 8 */
	BUSSTRESS_TEST_SOCP,                       /* 9 */
	BUSSTRESS_TEST_GU,                         /* 10 */
	BUSSTRESS_TEST_BBP,                        /* 11 */
	BUSSTRESS_TEST_BUTTOM                      /* 12 */
};

unsigned int g_busstress_test_en_run[BUSSTRESS_TEST_BUTTOM] =
{
	0,	/* BUSSTRESS_TEST_BBE16 					 */
	0,	/* BUSSTRESS_TEST_ACC				      */ /* ACC,CIPHER,KDF，只运行ACC即可 */
	0,	/* BUSSTRESS_TEST_CIPHER					 */
	0,	/* BUSSTRESS_TEST_KDF					 */
	0,	/* BUSSTRESS_TEST_EDMA					 */
	0,	/* BUSSTRESS_TEST_MDM_A9_AXIMEM2AXIMEM		 */
	1,	/* BUSSTRESS_TEST_MDM_A9_BBE16DTCM2BBE16DTCM  */
	0,	/* BUSSTRESS_TEST_MDM_A9_DDR2DDR			 */
	0,	/* BUSSTRESS_TEST_IPF					 */ /* C核IPF不必运行 */
	0,	/* BUSSTRESS_TEST_SOCP					 */
	0,	/* BUSSTRESS_TEST_GU					 */
	0	/* BUSSTRESS_TEST_BBP					 */
};

/*bus stress test switch*/
char *g_bbe16_move_type_str = NULL;

#define  SOCP_BUSSTRESS_TEST_DDR2DDR_SIZE   (10 * 1024)

#define A9_MEMCPY_BANDWIDTH_GET_CNT_MAX   1500
int g_get_a9_memcpy_bandwidth_delay = 6000;
double g_a9_memcpy_bandwidth_in_mbps[A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_TYPE_BUTTOM];
unsigned int g_a9_memcpy_bandwidth_cnt = 0;
OSL_TASK_ID g_taskid_get_a9_memcpy_bandwidth;

int get_a9_memcpy_bandwidth(void *para)
{
    
    int delay_ticks = *((int*)para);
	
    unsigned int memcpy_cnt_start_axi2axi = 0;
    unsigned int memcpy_cnt_start_dtcm2dtcm = 0;
    unsigned int memcpy_cnt_start_ddr2ddr = 0;
	
    unsigned int memcpy_cnt_end_axi2axi = 0;
    unsigned int memcpy_cnt_end_dtcm2dtcm = 0;
    unsigned int memcpy_cnt_end_ddr2ddr = 0;
	
	unsigned int memcpy_start_slice = 0;
	unsigned int memcpy_end_slice = 0;

    double time_delta_in_sec = 0;   /* 时间，单位:秒 */
	double data_trans_in_mbits[A9_MEMCPY_TYPE_BUTTOM] = {0};  /* 数据量，单位:Mbits */

	printf("------------------get_a9_memcpy_bandwidth delay_ticks = %d\n", delay_ticks);


	for (;;)
	{

	    /* axi_mem->axi_mem bbe16dtcm->bbe16dtcm ddr->ddr*/
		memcpy_start_slice = bsp_get_slice_value();
		memcpy_cnt_start_axi2axi = g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].ok_cnt;
		memcpy_cnt_start_dtcm2dtcm = g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt;
		memcpy_cnt_start_ddr2ddr = g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].ok_cnt;

		

		osl_task_delay(delay_ticks);
		
		printf("-----------g_a9_memcpy_bandwidth_cnt = %d\n", g_a9_memcpy_bandwidth_cnt);

		printf("start ---axi2axi[0x%08x] dtcm2dtcm[0x%08x] ddr2ddr[0x%08x]\n", memcpy_cnt_start_axi2axi, 
			memcpy_cnt_start_dtcm2dtcm, memcpy_cnt_start_ddr2ddr);

		memcpy_end_slice = bsp_get_slice_value();
		memcpy_cnt_end_axi2axi = g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].ok_cnt;
		memcpy_cnt_end_dtcm2dtcm = g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt;
		memcpy_cnt_end_ddr2ddr = g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].ok_cnt;
		printf("end ---axi2axi[0x%08x] dtcm2dtcm[0x%08x] ddr2ddr[0x%08x]\n", memcpy_cnt_end_axi2axi, 
			memcpy_cnt_end_dtcm2dtcm, memcpy_cnt_end_ddr2ddr);

		time_delta_in_sec = ((double)(get_timer_slice_delta(memcpy_start_slice, memcpy_end_slice))) / 32768;

		printf("-----------slice start 0x%08x end 0x%08x time_delta_in_sec = %f\n", memcpy_start_slice, memcpy_end_slice, time_delta_in_sec);

		data_trans_in_mbits[A9_MEMCPY_AXI2AXI] = ((double)(memcpy_cnt_end_axi2axi - memcpy_cnt_start_axi2axi)) * 
			                                     g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].size * 8 / 1024 /1024;
		data_trans_in_mbits[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM] = ((double)(memcpy_cnt_end_dtcm2dtcm - memcpy_cnt_start_dtcm2dtcm)) * 
			                                     g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].size * 8 / 1024 /1024;
		data_trans_in_mbits[A9_MEMCPY_DDR_2_DDR] = ((double)(memcpy_cnt_end_ddr2ddr - memcpy_cnt_start_ddr2ddr)) * 
			                                     g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].size * 8 / 1024 /1024;

		g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_AXI2AXI] = 
			           data_trans_in_mbits[A9_MEMCPY_AXI2AXI] / time_delta_in_sec;

		g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_BBE_DTCM_2_BBE_DTCM] = 
			           data_trans_in_mbits[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM] / time_delta_in_sec;

		g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_DDR_2_DDR] = 
			           data_trans_in_mbits[A9_MEMCPY_DDR_2_DDR] / time_delta_in_sec;


        printf("bandwidth axi2axi %f\n", 
			g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_AXI2AXI]);
        printf("bandwidth dtcm2dtcm %f\n", g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_BBE_DTCM_2_BBE_DTCM]);
        printf("bandwidth ddr2ddr %f\n", g_a9_memcpy_bandwidth_in_mbps[g_a9_memcpy_bandwidth_cnt % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_DDR_2_DDR]);
		
		g_a9_memcpy_bandwidth_cnt++;
		
	}
	
}

int a9_memcpy_bandwidth_show(void)
{
    unsigned int i = 0;

	for (i = 0; i < g_a9_memcpy_bandwidth_cnt; i++)
	{
	    printf("cnt %04d in mbps axi2axi %.4f dtcm2dtcm %.4f ddr2ddr %.4f\n", i, 
			g_a9_memcpy_bandwidth_in_mbps[i % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_AXI2AXI],
			g_a9_memcpy_bandwidth_in_mbps[i % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_BBE_DTCM_2_BBE_DTCM],
			g_a9_memcpy_bandwidth_in_mbps[i % A9_MEMCPY_BANDWIDTH_GET_CNT_MAX][A9_MEMCPY_DDR_2_DDR]);
		
	}

	return 0;

}

BSP_S32 busstress_test_start(int busstress_task_priority)
{
    int ret = 0;
	enum bbe16_move_type enum_bbe16_move_type = 0;

    g_busstress_test_start_time_stamp = bsp_get_slice_value();
    g_A9MemCpy_TaskPriority = busstress_task_priority;


    /* 首先运行BBE16，否则BBE16DTCM不可用 */
    bsp_bbe_load_muti();
    bsp_bbe_run();

    #if 0
	/* 将bbe16_dtcm的后12k字节中除了用于BBE16搬移目的的1k外，其余全部置为0xa5 */
	/* 用于socp搬移数据源的4k */
	memset((void*)BBE16_LOCAL_MEM_SOCP_ADDR, 0xaa, 0x1000);

	/* 用作bbe16搬移目的的1k字节 */

	/* 之后的7k */
	memset((void*)(BBE16_LOCAL_MEM_SOCP_ADDR + 5 * 1024), 0xaa, 7 * 1024);
	#endif

	/* BBE16  */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_BBE16])
	{
	    enum_bbe16_move_type = BBE16_MOVE_DDR_TO_BBE16DTCM;

	    if (BBE16_MOVE_DDR_TO_DDR == enum_bbe16_move_type)
		{
		    g_bbe16_move_type_str = "ddr->ddr ";
		}
		else if (BBE16_MOVE_DDR_TO_BBE16DTCM == enum_bbe16_move_type)
		{
			g_bbe16_move_type_str = "ddr->dtcm";
		}
		else
		{
			g_bbe16_move_type_str = "invalid  ";
		}

	    bsp_bbe_memcpy_stress_test_start(enum_bbe16_move_type);
		printf("bbe16 %s busstress test start ++++++ok\n", g_bbe16_move_type_str);
	}
	else
	{
		printf("bbe16 busstress no run******\n");
	}

	/* ACC */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_ACC])
	{
		ret = acc_stress_test_start(g_busstress_test_acc_task_priority, 0, cipher_stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore acc stress test start ------fail\n");
		}
		else
		{
			printf("ccore acc stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("acc busstress no run******\n");
	}

    /* CIPHER */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_CIPHER])
	{
		ret = cipher_stress_test_start(g_busstress_test_cipher_task_priority, cipher_stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore cipher stress test start -------fail\n");
		}
		else
		{
			printf("ccore cipher stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("cipher busstress no run******\n");
	}


    /* KDF */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_KDF])
	{
		ret = kdf_stress_test_start(g_busstress_test_kdf_task_priority, cipher_stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore kdf stress test start ------fail\n");
		}
		else
		{
			printf("ccore kdf stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("kdf busstress no run******\n");
	}

    #if 0
    /* EDMA */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_EDMA])
	{
		if(ERROR == edma_stress_test_start(g_busstress_test_edma_task_priority, stress_test_rate))
	        printf("ccore edma stress test fail\n");
	}
	#endif

	/* EDMA循环搬移模式，从DDR到BBE16DTCM */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_EDMA])
	{
		(void)edma_test_lli_loop(0x10);
		printf("ccore edma stress test start ++++++ok\n");
	}
	else
	{
		printf("edma busstress no run******\n");
	}

	/* MDM_A9 AXIMEM to AXIMEM*/
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_MDM_A9_AXIMEM2AXIMEM])
	{
		ret = a9_mem_stress_test_start_aximem2aximem(stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore mdm_a9 axi_mem to axi_mem stress test start ------fail\n");
		}
		else
		{
	        printf("ccore mdm_a9 axi_mem to axi_mem stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("mdm_a9 axi_mem to axi_mem busstress no run******\n");
	}

	/* MDM_A9 BBE16DTCM to BBE16DTCM */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_MDM_A9_BBE16DTCM2BBE16DTCM])
	{
	    ret = a9_mem_stress_test_start_bbe16dtcm2bbe16dtcm(stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore mdm_a9 bbe16_dtcm to bbe16_dtcm stress test start ------fail\n");
		}
		else
		{
	        printf("ccore mdm_a9 bbe16_dtcm to bbe16_dtcm stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("mdm_a9 bbe16_dtcm to bbe16_dtcm busstress no run******\n");
	}

	/* MDM_A9 DDR to DDR */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_MDM_A9_DDR2DDR])
	{
	    ret = a9_mem_stress_test_start_ddr2ddr(stress_test_rate);
		if (0 != ret)
		{
	        printf("ccore mdm_a9 ddr to ddr stress test start ------fail\n");
		}
		else
		{
	        printf("ccore mdm_a9 ddr to ddr stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("mdm_a9 ddr to ddr busstress no run******\n");
	}

	/*  起A9的统计任务*/
	ret = osl_task_init("A9BandWidth",g_busstress_test_get_a9_memcpy_bandwidth_task_priority,2000,
	      (OSL_TASK_FUNC)get_a9_memcpy_bandwidth,(void *)&g_get_a9_memcpy_bandwidth_delay,&g_taskid_get_a9_memcpy_bandwidth);
	if (-1 == ret)
	{
	    printf("get_a9_memcpy_bandwidth--------------start fail\n");
	}
	else
	{
	    printf("get_a9_memcpy_bandwidth++++++++++++++++++start ok\n");
	}
	

    /* IPF */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_IPF])
	{
	     ret = ipf_dl_stress_test_start(g_busstress_test_ipf_task_priority, stress_test_rate);
		 if (0 != ret)
		 {
			 printf("ccore ipf stress test start ------fail\n");
		 }
		 else
		 {
			 printf("ccore ipf stress test start ++++++ok\n");
		 }
    }
	else
	{
		printf("ipf busstress no run******\n");
	}


    /* SOCP*/
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_SOCP])
	{

		/* bbe16dtcm->ddr */
		ret = SOCP_ST_BUSSTRESS_TEST(g_busstress_test_socp_bbe16dtcm_to_ddr_task_priority,
		                       (u32)BBE16_LOCAL_MEM_SOCP_ADDR, (u32)BBE16_LOCAL_MEM_SOCP_SIZE);
		if (0 != ret)
		{
			printf("ccore socp bbe16dtcm->ddr stress test start ------fail\n");
		}
		else
		{
			printf("ccore socp bbe16dtcm->ddr stress test start ++++++ok\n");
		}


	}
	else
	{
		printf("socp busstress no run******\n");
	}


    /* GU */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_GU])
	{
		ret = gu_master_stress_test_start(g_busstress_test_gu_master_task_priority, stress_test_rate);
		if (0 != ret)
		{
			printf("ccore gu stress test start ------fail ret=%d\n", ret);
		}
		else
		{
			printf("ccore gu stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("gu busstress no run******\n");
	}

    /* BBP */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_BBP])
	{
		ret = bbp_busstress_test_spawn_task(g_busstress_test_bbp_task_priority);//bbp_dma_stress_test(0xE1000800, 1024, 0, 8);
		if (0 != ret)
		{
			printf("ccore bbp stress test start ------fail\n");
		}
		else
		{
			printf("ccore bbp stress test start ++++++ok\n");
		}
	}
	else
	{
		printf("bbp busstress no run******\n");
	}

    /* 启动监控*/
	ret = busstress_test_start_monitor(busstress_task_priority);
    if (0 != ret)
	{
	    printf("busstress_test_start_monitor err ret=%d\n", ret);
	}

	return OK;
}

BSP_S32 busstress_test_stop(void)
{
	if(0 != edma_stress_test_stop())
        printf("ccore edma stress test stop fail\n");
#if 0
	if(0 != acc_stress_test_stop())
        printf("ccore acc stress test0 stop fail\n");

	if(0 != cipher_stress_test_stop())
        printf("ccore cipher stress test stop fail\n");

	if(0 != kdf_stress_test_stop())
        printf("ccore kdf stress test stop fail\n");
#endif
    if(0 != a9_mem_stress_test_stop_use_aximem64())
        printf("ccore use aximem64 stress test stop fail\n");

    if(0 != a9_mem_stress_test_stop_use_bbe16())
        printf("ccore use bbe16 dtcm stress test stop fail\n");

    if(0 != a9_mem_stress_test_stop_use_ddr())
        printf("ccore use ddr stress test stop fail\n");

	if(0 != ipf_dl_stress_test_stop())
        printf("ccore ipf dl stress test fail\n");

	//if(0 != a9_mem_stress_test_stop_use_bbe16())
    //    printf("ccore use bbe16 stress test fail\n",0,0,0,0,0,0);


	if(0 != gu_master_stress_test_stop())
        printf("gu_master_stress_test_stop stress test fail\n");

	return OK;
}

unsigned int g_bbe16_busstress_test_ok_cnt = 0;
unsigned int g_bbe16_busstress_test_fail_cnt = 0;
unsigned int g_bbe16_busstress_test_ok_last_cnt = 0;
unsigned int g_bbe16_busstress_test_fail_last_cnt = 0;

void busstress_info_print()
{
    int bbe16_memcpy_times = bsp_bbe_memcpy_stress_test_result();

    printk("ddr_memcpy_test info begin:\n");
    printk("BBE16 memcpy times: %d\n", bbe16_memcpy_times);
    printk("ddr_memcpy_test info end:\n");
}

extern unsigned int g_acc_busstress_test_ok_cnt;
extern unsigned int g_acc_busstress_test_fail_cnt;
extern unsigned int g_cipher_busstress_test_ok_cnt;
extern unsigned int g_cipher_busstress_test_fail_cnt;
extern unsigned int g_kdf_busstress_test_ok_cnt;
extern unsigned int g_kdf_busstress_test_fail_cnt;
extern u32 g_edma_busstress_test_ok_cnt[EDMA_MOVE_TYPE_BUTTOM];
extern u32 g_edma_busstress_test_fail_cnt[EDMA_MOVE_TYPE_BUTTOM];
extern unsigned int g_ipf_busstress_test_ok_cnt;
extern unsigned int g_ipf_busstress_test_fail_cnt;
#if _CICOM0_TRANS
extern unsigned int g_cicom0_busstress_test_ok_cnt;
extern unsigned int g_cicom0_busstress_test_fail_cnt;
#endif
#if _CICOM1_TRANS
extern unsigned int g_cicom1_busstress_test_ok_cnt;
extern unsigned int g_cicom1_busstress_test_fail_cnt;
#endif
#if _UPACC_TRANS
extern unsigned int g_upacc_busstress_test_ok_cnt;
extern unsigned int g_upacc_busstress_test_fail_cnt;
#endif
extern unsigned int g_socp_bus_test_ddr_to_ddr_ok_cnt;
extern unsigned int g_socp_bus_test_ddr_to_ddr_fail_cnt;
extern unsigned int g_socp_bus_test_axi_mem_to_ddr_ok_cnt;
extern unsigned int g_socp_bus_test_axi_mem_to_ddr_fail_cnt;
extern unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt;
extern unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt;
extern unsigned int g_bbp_busstress_test_ok_cnt;
extern unsigned int g_bbp_busstress_test_fail_cnt;


/*  上一次打印时的次数*/
unsigned int g_acc_busstress_test_ok_last_cnt = 0;
unsigned int g_acc_busstress_test_fail_last_cnt = 0;
unsigned int g_cipher_busstress_test_ok_last_cnt = 0;
unsigned int g_cipher_busstress_test_fail_last_cnt = 0;
unsigned int g_kdf_busstress_test_ok_last_cnt = 0;
unsigned int g_kdf_busstress_test_fail_last_cnt = 0;
u32 g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_TYPE_BUTTOM] = {0};
u32 g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_TYPE_BUTTOM] = {0};
unsigned int g_ipf_busstress_test_ok_last_cnt = 0;
unsigned int g_ipf_busstress_test_fail_last_cnt = 0;
#if _CICOM0_TRANS
unsigned int g_cicom0_busstress_test_ok_last_cnt = 0;
unsigned int g_cicom0_busstress_test_fail_last_cnt = 0;
#endif
#if _CICOM1_TRANS
unsigned int g_cicom1_busstress_test_ok_last_cnt = 0;
unsigned int g_cicom1_busstress_test_fail_last_cnt = 0;
#endif
#if _UPACC_TRANS
unsigned int g_upacc_busstress_test_ok_last_cnt = 0;
unsigned int g_upacc_busstress_test_fail_last_cnt = 0;
#endif
unsigned int g_socp_bus_test_ddr_to_ddr_ok_last_cnt = 0;
unsigned int g_socp_bus_test_ddr_to_ddr_fail_last_cnt = 0;
unsigned int g_socp_bus_test_axi_mem_to_ddr_ok_last_cnt = 0;
unsigned int g_socp_bus_test_axi_mem_to_ddr_fail_last_cnt = 0;
unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_ok_last_cnt = 0;
unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_fail_last_cnt = 0;
unsigned int g_bbp_busstress_test_ok_last_cnt = 0;
unsigned int g_bbp_busstress_test_fail_last_cnt = 0;


/* 注意:如果BBE16没有跑起来，获取g_bbe16_busstress_test_ok_cnt时会挂死 */
int busstress_test_show_cnt(void)
{
    g_busstress_test_now_time_stamp = bsp_get_slice_value();

	printf("------------------busstress test cnt info start-------------------\n");

    printf("test start time_stamp 0x%x and now time_stamp 0x%x\n", g_busstress_test_start_time_stamp, g_busstress_test_now_time_stamp);

    printf("master--------------------------[ok_cnt]    [ok_cnt_delta] [fail_cnt] [fail_cnt_delta]\n");

	/**************acc*****************/
	printf("acc-----------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_acc_busstress_test_ok_cnt,
											g_acc_busstress_test_ok_cnt - g_acc_busstress_test_ok_last_cnt,
	                                                                           g_acc_busstress_test_fail_cnt,
                                            g_acc_busstress_test_fail_cnt - g_acc_busstress_test_fail_last_cnt);

    g_acc_busstress_test_ok_last_cnt = g_acc_busstress_test_ok_cnt;
	g_acc_busstress_test_fail_last_cnt = g_acc_busstress_test_fail_cnt;

	/**************cipher*****************/
	printf("cipher--------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_cipher_busstress_test_ok_cnt,
										g_cipher_busstress_test_ok_cnt - g_cipher_busstress_test_ok_last_cnt,
										                                       g_cipher_busstress_test_fail_cnt,
										g_cipher_busstress_test_fail_cnt - g_cipher_busstress_test_fail_last_cnt);
	g_cipher_busstress_test_ok_last_cnt = g_cipher_busstress_test_ok_cnt;
	g_cipher_busstress_test_fail_last_cnt = g_cipher_busstress_test_fail_cnt;

	/**************kdf*****************/
	printf("kdf-----------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_kdf_busstress_test_ok_cnt,
											g_kdf_busstress_test_ok_cnt - g_kdf_busstress_test_ok_last_cnt,
																			g_kdf_busstress_test_fail_cnt,
										g_kdf_busstress_test_fail_cnt - g_kdf_busstress_test_fail_last_cnt);
	g_kdf_busstress_test_ok_last_cnt = g_kdf_busstress_test_ok_cnt;
	g_kdf_busstress_test_fail_last_cnt = g_kdf_busstress_test_fail_cnt;

	/**************edma*****************/
	printf("edma ddr->ddr-------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_DDR],
					g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_DDR] - g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_DDR],
								                                              g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_DDR],
					g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_DDR] - g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_DDR]);
     g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_DDR] = g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_DDR];
	 g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_DDR] = g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_DDR];


    printf("edma ddr->axi_mem---------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_AXI_MEM],
					   g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_AXI_MEM] - g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_AXI_MEM],
																				 g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_AXI_MEM],
					   g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_AXI_MEM] - g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_AXI_MEM]);
		g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_AXI_MEM] = g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_AXI_MEM];
		g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_AXI_MEM] = g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_AXI_MEM];
    printf("edma axi_mem->axi_mem-----------0x%08x  0x%08x     0x%08x 0x%08x\n", g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM],
					   g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM] - g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM],
																				 g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM],
					   g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM] - g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM]);
		g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM] = g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM];
		g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM] = g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_AXI_MEM];
    printf("edma axi_mem->ddr---------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_DDR],
					   g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_DDR] - g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_AXI_MEM_TO_DDR],
																				 g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_DDR],
					   g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_DDR] - g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_AXI_MEM_TO_DDR]);
		g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_AXI_MEM_TO_DDR] = g_edma_busstress_test_ok_cnt[EDMA_MOVE_AXI_MEM_TO_DDR];
		g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_AXI_MEM_TO_DDR] = g_edma_busstress_test_fail_cnt[EDMA_MOVE_AXI_MEM_TO_DDR];
    printf("edma ddr->bbe16_dtcm------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM],
					   g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM] - g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM],
																				 g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM],
					   g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM] - g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM]);
		g_edma_busstress_test_ok_last_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM] = g_edma_busstress_test_ok_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM];
		g_edma_busstress_test_fail_last_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM] = g_edma_busstress_test_fail_cnt[EDMA_MOVE_DDR_TO_BBE16_DTCM];

    /****************a9******************/
	printf("a9  axi_mem to axi_mem----------0x%08x  0x%08x     0x%08x 0x%08x\n", g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].ok_cnt,
				g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].ok_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_AXI2AXI].ok_cnt,
				                                                             g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].fail_cnt,
				g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].fail_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_AXI2AXI].fail_cnt);
	  g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_AXI2AXI].ok_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].ok_cnt;
	  g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_AXI2AXI].fail_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_AXI2AXI].fail_cnt;


    printf("a9  bbe16_dtcm to bbe16_dtcm----0x%08x  0x%08x     0x%08x 0x%08x\n", g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt,
				  g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt,
																			   g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].fail_cnt,
				  g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].fail_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].fail_cnt);
		g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].ok_cnt;
		g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].fail_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_BBE_DTCM_2_BBE_DTCM].fail_cnt;
    #if 0
	printf("a9  ddr to ddr------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].ok_cnt,
				  g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].ok_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_DDR_2_DDR].ok_cnt,
																			   g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].fail_cnt,
				  g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].fail_cnt - g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_DDR_2_DDR].fail_cnt);
		g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_DDR_2_DDR].ok_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].ok_cnt;
		g_a9_memcpy_tsk_param_last_time[A9_MEMCPY_DDR_2_DDR].fail_cnt = g_a9_memcpy_tsk_param[A9_MEMCPY_DDR_2_DDR].fail_cnt;
    #endif
    /****************ipf******************/
	printf("ipf-----------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_ipf_busstress_test_ok_cnt,
											g_ipf_busstress_test_ok_cnt - g_ipf_busstress_test_ok_last_cnt,
																				g_ipf_busstress_test_fail_cnt,
										g_ipf_busstress_test_fail_cnt - g_ipf_busstress_test_fail_last_cnt);
	g_ipf_busstress_test_ok_last_cnt = g_ipf_busstress_test_ok_cnt;
	g_ipf_busstress_test_fail_last_cnt = g_ipf_busstress_test_fail_cnt;

    /****************socp******************/
	printf("socp ddr->ddr-------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_socp_bus_test_ddr_to_ddr_ok_cnt,
									g_socp_bus_test_ddr_to_ddr_ok_cnt - g_socp_bus_test_ddr_to_ddr_ok_last_cnt,
																			g_socp_bus_test_ddr_to_ddr_fail_cnt,
									g_socp_bus_test_ddr_to_ddr_fail_cnt - g_socp_bus_test_ddr_to_ddr_fail_last_cnt);
	g_socp_bus_test_ddr_to_ddr_ok_last_cnt = g_socp_bus_test_ddr_to_ddr_ok_cnt;
	g_socp_bus_test_ddr_to_ddr_fail_last_cnt = g_socp_bus_test_ddr_to_ddr_fail_cnt;
	printf("socp axi_mem->ddr---------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_socp_bus_test_axi_mem_to_ddr_ok_cnt,
							    g_socp_bus_test_axi_mem_to_ddr_ok_cnt - g_socp_bus_test_axi_mem_to_ddr_ok_last_cnt,
																			g_socp_bus_test_axi_mem_to_ddr_fail_cnt,
								g_socp_bus_test_axi_mem_to_ddr_fail_cnt - g_socp_bus_test_axi_mem_to_ddr_fail_last_cnt);
		g_socp_bus_test_axi_mem_to_ddr_ok_last_cnt = g_socp_bus_test_axi_mem_to_ddr_ok_cnt;
		g_socp_bus_test_axi_mem_to_ddr_fail_last_cnt = g_socp_bus_test_axi_mem_to_ddr_fail_cnt;
	printf("socp bbe16dtcm->ddr-------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt,
								g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt - g_socp_bus_test_bbe16dtcm_to_ddr_ok_last_cnt,
																				g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt,
								g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt - g_socp_bus_test_bbe16dtcm_to_ddr_fail_last_cnt);
			g_socp_bus_test_bbe16dtcm_to_ddr_ok_last_cnt = g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt;
			g_socp_bus_test_bbe16dtcm_to_ddr_fail_last_cnt = g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt;

    /****************bbe16******************/
	g_bbe16_busstress_test_ok_cnt = bsp_bbe_memcpy_stress_test_result();
	printf("bbe16  %s----------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_bbe16_move_type_str, g_bbe16_busstress_test_ok_cnt,
													    g_bbe16_busstress_test_ok_cnt - g_bbe16_busstress_test_ok_last_cnt,
																							g_bbe16_busstress_test_fail_cnt,
													g_bbe16_busstress_test_fail_cnt - g_bbe16_busstress_test_fail_last_cnt);
		g_bbe16_busstress_test_ok_last_cnt = g_bbe16_busstress_test_ok_cnt;
		g_bbe16_busstress_test_fail_last_cnt = g_bbe16_busstress_test_fail_cnt;

	/****************cicom0******************/
#if _CICOM0_TRANS
	printf("cicom0--------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_cicom0_busstress_test_ok_cnt,
									g_cicom0_busstress_test_ok_cnt - g_cicom0_busstress_test_ok_last_cnt,
																		g_cicom0_busstress_test_fail_cnt,
							g_cicom0_busstress_test_fail_cnt - g_cicom0_busstress_test_fail_last_cnt);
    g_cicom0_busstress_test_ok_last_cnt = g_cicom0_busstress_test_ok_cnt;
	g_cicom0_busstress_test_fail_last_cnt = g_cicom0_busstress_test_fail_cnt;
#endif

    /****************cicom1******************/
#if _CICOM1_TRANS
	printf("cicom1--------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_cicom1_busstress_test_ok_cnt,
									g_cicom1_busstress_test_ok_cnt - g_cicom1_busstress_test_ok_last_cnt,
																		g_cicom1_busstress_test_fail_cnt,
							g_cicom1_busstress_test_fail_cnt - g_cicom1_busstress_test_fail_last_cnt);
    g_cicom1_busstress_test_ok_last_cnt = g_cicom1_busstress_test_ok_cnt;
	g_cicom1_busstress_test_fail_last_cnt = g_cicom1_busstress_test_fail_cnt;
#endif

    /****************upacc******************/
#if _UPACC_TRANS
	printf("upacc---------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_upacc_busstress_test_ok_cnt,
										g_upacc_busstress_test_ok_cnt - g_upacc_busstress_test_ok_last_cnt,
																			g_upacc_busstress_test_fail_cnt,
									g_upacc_busstress_test_fail_cnt - g_upacc_busstress_test_fail_last_cnt);
    g_upacc_busstress_test_ok_last_cnt = g_upacc_busstress_test_ok_cnt;
	g_upacc_busstress_test_fail_last_cnt = g_upacc_busstress_test_fail_cnt;
#endif


    /* BBP */
	printf("bbp-----------------------------0x%08x  0x%08x     0x%08x 0x%08x\n", g_bbp_busstress_test_ok_cnt,
											g_bbp_busstress_test_ok_cnt - g_bbp_busstress_test_ok_last_cnt,
																			g_bbp_busstress_test_fail_cnt,
										g_bbp_busstress_test_fail_cnt - g_bbp_busstress_test_fail_last_cnt);

		g_bbp_busstress_test_ok_last_cnt = g_bbp_busstress_test_ok_cnt;
		g_bbp_busstress_test_fail_last_cnt = g_bbp_busstress_test_fail_cnt;


	printf("-------------------busstress test cnt info end------------------\n");


    return 0;
}

int busstress_test_bbe16dtcm_cmp(void)
{
    unsigned char *ptr = (unsigned char *)BBE16_LOCAL_MEM_SOCP_ADDR;
	int i = 0;
	unsigned int not_equl_bytes = 0;

    /* 先比对前4k字节 */
	for (i = 0; i < 4 * 1024; i++)
	{
	    if (0xa5 != ptr[i])
    	{
    	    not_equl_bytes++;
    	    printf("ptr[0x%04x] = 0x%02x\n", i, ptr[i]);
    	}
	}

	/* 不比对用于BBE16搬移目的的1k */

	/* 再比对之后的7k */
	for (i = 5 * 1024; i < 12 * 1024; i++)
	{
	    if (0xa5 != ptr[i])
    	{
    	    not_equl_bytes++;
    	    printf("ptr[0x%04x] = 0x%02x\n", i, ptr[i]);
    	}
	}

	printf("not_equl_bytes = 0x%08x\n", not_equl_bytes);



    return 0;
}

