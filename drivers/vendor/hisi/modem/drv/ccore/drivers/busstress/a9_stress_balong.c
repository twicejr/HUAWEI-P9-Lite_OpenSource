#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <osl_thread.h>
#include <osl_cache.h>
#include <osl_types.h>
#include "product_config.h"
#include "hi_base.h"
#include "hi_syssc.h"
#include "hi_syscrg.h"
#include "mdrv.h"
#include "bsp_om.h"
#include "drv_comm.h"
#include "bsp_busstress.h"
#include "amon_balong.h"
#define M1_PORT_BW  (u64)(2ULL<<32ULL)
#define SOC_PORT_BW (u64)(1ULL<<35ULL)

BSP_BOOL g_bA9MemCpyTaskRun = BSP_FALSE;
BSP_U32 ccpu_busstress_count = 0;
BSP_S32 stress_test_rate = 2;
BSP_S32 cipher_stress_test_rate = 8;
extern BSP_S32 edma_stress_test_start(BSP_S32 task_priority, BSP_S32 test_rate);
extern BSP_S32 edma_stress_test_stop();
extern BSP_S32 acc_stress_test_start(BSP_S32 task_priority,BSP_S32 test_type,BSP_S32 test_rate);
extern BSP_S32 acc_stress_test_stop();
extern BSP_S32 cipher_stress_test_start(BSP_S32 task_priority,BSP_S32 test_rate);
extern BSP_S32 cipher_stress_test_stop();
extern BSP_S32 kdf_stress_test_start(BSP_S32 task_priority,BSP_S32 test_rate);
extern BSP_S32 kdf_stress_test_stop();
extern s32 edma_test_lli_loop_ddr(enum edma_req_id req );
extern s32 edma_test_lli_loop_sram(enum edma_req_id req );
#ifdef CONFIG_PSAM
int psam_dl_stress_test_start(int task_priority,unsigned int dtime);
int psam_dl_stress_test_stop();
int psam_cipher_dl_stress_test_start(int task_priority,int dtime);
int psam_cipher_dl_stress_test_stop();
#else
extern BSP_S32 ipf_dl_stress_test_start(BSP_S32 task_priority,BSP_S32 dtime);
extern BSP_S32 ipf_dl_stress_test_stop();
#endif
extern int for_hsuart_busstress_test_start(void);
extern int for_hsuart_busstress_test_stop(void);
extern int bsp_bbe_stress_test_start(void);
extern int gu_master_stress_test_start(int task_priority,int delayticks);
extern int gu_master_stress_test_stop();

#define  printf(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_STRESS, "[A9 strss test]: "fmt, ##__VA_ARGS__))
#define  ver_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_VERSION, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

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
		memcpyTestProcess(u32Src,u32Dst,s32Size);
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
BSP_S32 g_A9MemCpy_TaskPriority = 51;
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
BSP_S32 g_ddr_para[4];
BSP_S32 g_srm_para[4];
BSP_U32 g_ddr_period = 0x100;
void a9_ddr_busstress_period_modify(BSP_U32 count)
{
	g_ddr_period = count;
	printf("corrent period is :%d\n",g_ddr_period);
	return ;
} 
void a9_ddr_busstress_period_get(void)
{
	printf("corrent period is :%d\n",g_ddr_period);
	return ;
} 
BSP_S32 a9MemcpyTestFuncExt(BSP_U32 *para)
{
	BSP_U32 u32Cnt = 0;
	BSP_U32 u32Src     = para[0];
	BSP_U32 u32Dst     = para[1];
	BSP_S32 s32Size    = para[2];
	BSP_S32 s32DelayVal= para[3];

	while(g_bA9MemCpyTaskRunExt)
	{
		if(0 != memcpyTestProcess(u32Src,u32Dst,s32Size))
		{
			printf("error!u32Src:0x%x,u32Dst:0x%x.\n",u32Src,u32Dst);
			break;
		}
	        (BSP_VOID)osl_cache_flush(OSL_DATA_CACHE, (BSP_VOID *)u32Src, s32Size);
	        (BSP_VOID)osl_cache_flush(OSL_DATA_CACHE, (BSP_VOID *)u32Dst, s32Size);
		ccpu_busstress_count++;
		u32Cnt++;
		if(0 == (u32Cnt%g_ddr_period))
		{
			osl_task_delay(s32DelayVal);
		}
		if(0 == (u32Cnt%100000))
		{
			if((unsigned int)AXI_MEM_64_SRC_FOR_A9_CCORE == u32Src){
				printf("AXI MEM for ");
			}
			else{
				printf("DDR     for ");
			}
			printf("MDM A9 memcopy test count is %d\n",u32Cnt);
		}
	}
	return BSP_OK;
}
BSP_S32 a9MemcpyTaskSpawnExt(BSP_U32 u32Src,BSP_U32 u32Dst,BSP_S32 s32Size,BSP_S32 s32DelayValue)
{
	char taskName[30] = {0};
	BSP_S32 s32Ret = 0;
    BSP_S32 s32LocalDelayVal = s32DelayValue;
	if((unsigned int)AXI_MEM_64_SRC_FOR_A9_CCORE == u32Src){
		g_srm_para[0] = u32Src;
		g_srm_para[1] = u32Dst;
		g_srm_para[2] = s32Size;
		g_srm_para[3] = s32DelayValue;
	}
	else{
		g_ddr_para[0] = u32Src;
		g_ddr_para[1] = u32Dst;
		g_ddr_para[2] = s32Size;
		g_ddr_para[3] = s32DelayValue;
	}
	if(0 == s32LocalDelayVal)
	{
		s32LocalDelayVal = 1;
	}

	sprintf(taskName,"a9MemcpyTask%x",u32Src);
	g_bA9MemCpyTaskRunExt = BSP_TRUE;
	s32Ret = osl_task_init(taskName,g_A9MemCpy_TaskPriority,0x2000,(OSL_TASK_FUNC)a9MemcpyTestFuncExt,(void *)g_ddr_para,&g_bA9taskid);
	if(ERROR == s32Ret)
	{
		printf("taskSpawn %s fail.\n",taskName);
		return ERROR;		
	}
	
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


BSP_S32 a9_mem_stress_test_start_use_ddr(BSP_S32 s32DelayValue)
{
	void *src_addr;
	void *dst_addr;
	src_addr = malloc(DDR_MEM_SIZE_FOR_A9);
	if(NULL == src_addr)
	{
		return ERROR;
	}
	dst_addr = malloc(DDR_MEM_SIZE_FOR_A9);
	if(NULL == dst_addr)
	{
        free(src_addr);
		return ERROR;
	}

	a9MemcpyTaskSpawnExt((BSP_S32)src_addr, (BSP_S32)dst_addr,DDR_MEM_SIZE_FOR_A9,s32DelayValue);
	return OK;
}


BSP_S32 a9_mem_stress_test_start_use_bbe16(BSP_S32 s32DelayValue)
{
	a9MemcpyTaskSpawnExt(BBE_TCM_ADDR,BBE_TCM_ADDR + BBE16_LOCAL_MEM_SIZE_FOR_A9 ,BBE16_LOCAL_MEM_SIZE_FOR_A9,s32DelayValue);
	return OK;
}
BSP_S32 a9_mem_stress_test_stop_use_bbe16()
{
	a9MemcpyTaskDeleteExt(BBE_TCM_ADDR);
	return OK;
}

BSP_S32 a9_mem_stress_test_start_use_hifi(BSP_S32 s32DelayValue)
{
	BSP_S32 reg = 0x1C0000;  
	/*?a?¡ä??*/
 	writel(reg, 0x90000070);  
	a9MemcpyTaskSpawnExt(HIFI_TCM_ADDR,HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR,HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE,s32DelayValue);
	return OK;
}
BSP_S32 a9_mem_stress_test_stop_use_hifi()
{
	a9MemcpyTaskDeleteExt(HIFI_TCM_ADDR);
	return OK;
}
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
BSP_S32 a9_mem_stress_test_start_use_aximem64(BSP_S32 s32DelayValue)
{
	a9MemcpyTaskSpawnExt((unsigned int)AXI_MEM_64_SRC_FOR_A9_CCORE,(unsigned int)AXI_MEM_64_DST_FOR_A9_CCORE,AXI_MEM_FOR_MEMCPY_SIZE,s32DelayValue);
	return OK;
}

BSP_S32 a9_mem_stress_test_start_use_aximem64_count()
{
	printf("ccpu busstress count: %u", ccpu_busstress_count);
	return OK;
}

BSP_S32 a9_mem_stress_test_stop_use_aximem64()
{
	a9MemcpyTaskDeleteExt((unsigned int)AXI_MEM_64_SRC_FOR_A9_CCORE);
	return OK;
}
u32 amon_debug = 1;
u32 g_amon_priority = 40;
OSL_TASK_ID g_amon_taskid;
s32 amon_stop(axi_config_enum_uint32 config);
void amon_printf(char * strings , unsigned int addr ,u64 bw)
{
	long long amon_val;
	double    usage = 0;
	amon_val = readl(addr + 4);
	amon_val = (amon_val << 32 ) | readl(addr);
	usage = ((double)amon_val / bw )*100;
	printf("%s:%3.4f\n",strings,usage);

}
void amon_printf_reg(char * strings , unsigned int addr)
{
	u32 amon_val = readl(addr);
	printf("%s:0x%x\n",strings,amon_val);
}
void bsp_amonitor_show(void)
{
    unsigned int amon_cnt_flag = 0;
	char * strings = NULL;
	strings = malloc(100);
    //------------------------
    //Initial
    //------------------------
    writel(0x00840180, 0x90000800);
	writel(0x00020000, 0x8020040c);
    writel(0xe, 0x96000004);
    writel(0xe, 0x80458004);
    writel(0xffffffff, 0x96000028);
    writel(0xffffffff, 0x80458028);
    while(amon_debug){ 
		//////////////////////////////// Phase1. glb/mdm ports monitor
		
		//------------------------
		//DW_axi_glb Ports monitor
		//------------------------
		//reset
		writel(0x20000000, 0x90000060);
		writel(0x20000000, 0x90000064);
		//amon soft reset
		writel(0x2, 0x96000000);
		//ports cfg
		writel(0x2c688, 0x9600001C);
		//ID cfg
		writel(0x0, 0x96000100);
		writel(0x0, 0x96000200);
		writel(0x0, 0x96000300);
		writel(0x0, 0x96000400);
		writel(0x0, 0x96000500);
		writel(0x0, 0x96000600);
		
		//------------------------
		//DW_axi_mdm Ports monitor
		//------------------------
		//reset
		writel(0x20000000, 0x80200020);
		writel(0x20000000, 0x80200024);
		//amon soft reset
		writel(0x2, 0x80458000);
		//ports cfg
		writel(0x2c688, 0x8045801C);
		//ID cfg
		writel(0x0, 0x80458100);
		writel(0x0, 0x80458200);
		writel(0x0, 0x80458300);
		writel(0x0, 0x80458400);
		
		//Int. clear
		writel(0xffffffff, 0x96000020);
		writel(0xffffffff, 0x80458020);    
		//start amon
		writel(0x00840580, 0x90000800);
		writel(0x00020400, 0x8020040C);
		
		//waitting for monitor finish
		amon_cnt_flag = 0;
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(300);
			amon_cnt_flag = readl(0x96000008);
		}
		amon_cnt_flag = readl(0x80458008);
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(1);
			amon_cnt_flag = readl(0x80458008);
		}
		
		//amon stop
		writel(0x00840180, 0x90000800);
		writel(0x00020000, 0x8020040C);
		
		//get results
		printf("--------------------------------------------\n");
		printf("--- Balong V700R500 bus stress statistic ---\n");
		printf("--------------------------------------------\n");
		strings ="SOC:ACPU_M1\t\tRD count";
		amon_printf(strings, 0x960001e8,M1_PORT_BW);			
		strings ="SOC:M3\t\t\tRD count";
		amon_printf(strings, 0x960002e8,SOC_PORT_BW);
		strings = "SOC:ACPU_M0\t\tRD count"; //AMON_SOC PORT2: ACPU_M0  arlen(bytes)
		amon_printf(strings, 0x960003e8,SOC_PORT_BW);		
		strings ="SOC:HIFI\t\tRD count";//AMON_SOC PORT3: HIFI	 arlen(bytes)
		amon_printf(strings, 0x960004e8,SOC_PORT_BW);
		strings ="SOC:PERI_MST\t\tRD count" ; //AMON_SOC PORT4: PERI_MST arlen(bytes)
		amon_printf(strings, 0x960005e8,SOC_PORT_BW);
		strings ="SOC:PCIE_BRG\t\tRD count" ; //AMON_SOC PORT5: PCIE_BRG arlen(bytes)
		amon_printf(strings, 0x960006e8,SOC_PORT_BW);
		strings ="SOC:ACPU_M1\t\tWR count" ; //AMON_SOC PORT0: ACPU_M1:awlen(bytes)
		amon_printf(strings, 0x960001f0,M1_PORT_BW);
		strings ="SOC:M3\t\t\tWR count" ; //AMON_SOC PORT1: M3		 awlen(bytes)
		amon_printf(strings, 0x960002f0,SOC_PORT_BW);
		strings ="SOC:ACPU_M0\t\tWR count" ; //AMON_SOC PORT2: ACPU_M0  awlen(bytes)
		amon_printf(strings, 0x960003f0,SOC_PORT_BW);
		strings ="SOC:HIFI\t\tWR count" ; //AMON_SOC PORT3: HIFI	 awlen(bytes)
		amon_printf(strings, 0x960004f0,SOC_PORT_BW);
		strings ="SOC:PERI_MST\t\tWR count" ; //AMON_SOC PORT4: PERI_MST awlen(bytes)
		amon_printf(strings, 0x960005f0,SOC_PORT_BW);
		strings ="SOC:PCIE_BRG\t\tWR count" ; //AMON_SOC PORT5: PCIE_BRG awlen(bytes)	
		amon_printf(strings, 0x960006f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");
		
		strings ="MDM:CCPU_M1\t\tRD count" ; //AMON_MDM PORT0: CCPU_M1  arlen(bytes)
		amon_printf(strings, 0x804581e8,M1_PORT_BW);
		strings ="MDM:BBP_BRG\t\tRD count" ; //AMON_MDM PORT1: BBP_BRG  arlen(bytes)
		amon_printf(strings, 0x804582e8,SOC_PORT_BW);
		strings ="MDM:ACPU_M0\t\tRD count" ; //AMON_MDM PORT2: CCPU_M0  arlen(bytes)
		amon_printf(strings, 0x804583e8,SOC_PORT_BW);
		strings ="MDM:PERI_MST\t\tRD count" ; //AMON_MDM PORT3: PERI_MST arlen(bytes)
		amon_printf(strings, 0x804584e8,SOC_PORT_BW);
		strings ="MDM:CCPU_M1\t\tWR count" ; //AMON_MDM PORT0: CCPU_M1  awlen(bytes)
		amon_printf(strings, 0x804581f0,M1_PORT_BW);
		strings ="MDM:BBP_BRG\t\tWR count" ; //AMON_MDM PORT1: BBP_BRG  awlen(bytes)
		amon_printf(strings, 0x804582f0,SOC_PORT_BW);
		strings ="MDM:CCPU_M0\t\tWR count" ; //AMON_MDM PORT2: CCPU_M0  awlen(bytes)
		amon_printf(strings, 0x804583f0,SOC_PORT_BW);
		strings ="MDM:PERI_MST\t\tWR count" ; //AMON_MDM PORT3: PERI_MST awlen(bytes)
		amon_printf(strings, 0x804584f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");
		//////////////////////////////// Phase2. soc/mdm peri_mst ports monitor
		
		//------------------------
		//soc peri_mst ports
		//------------------------
		//reset
		writel(0x20000000, 0x90000060);
		writel(0x20000000, 0x90000064);
		//amon soft reset
		writel(0x2, 0x96000000);
		//ports cfg
		writel(0x924924, 0x9600001C);
		//ID cfg
		writel(0x80078000, 0x96000100);
		writel(0x80078010, 0x96000200);
		writel(0x80078020, 0x96000300);
		writel(0x80078030, 0x96000400);
		writel(0x80078040, 0x96000500);
		writel(0x80078050, 0x96000600);
		writel(0x80078060, 0x96000700);
		writel(0x80078070, 0x96000800);
		
		//------------------------
		//mdm peri_mst ports
		//------------------------	 
		//reset
		writel(0x20000000, 0x80200020);
		writel(0x20000000, 0x80200024);
		//amon soft reset
		writel(0x2, 0x80458000);
		//ports cfg
		writel(0x1b6db, 0x8045801C);
		//ID cfg
		writel(0x80078000, 0x80458100);
		writel(0x80078010, 0x80458200);
		writel(0x80078020, 0x80458300);
		writel(0x80078030, 0x80458400);
		writel(0x80078040, 0x80458500);
		writel(0x80078050, 0x80458600); 
		
		//Int. clear
		writel(0xffffffff, 0x96000020);
		writel(0xffffffff, 0x80458020);
		//start amon
		writel(0x00840580, 0x90000800);
		writel(0x00020400, 0x8020040C);    
		
		//waitting for monitor finish
		amon_cnt_flag = 0;
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(10000);
			amon_cnt_flag = readl(0x96000008);
		}
		amon_cnt_flag = readl(0x80458008);
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(1);
			amon_cnt_flag = readl(0x80458008);
		}
		
		//amon stop
		writel(0x00840180, 0x90000800);
		writel(0x00020000, 0x8020040C);
		
		//get results
		strings ="SOC:EDMA\t\tRD count" ; //AMON_SOC PORT0: EDMA		 arlen(bytes)
		amon_printf(strings, 0x960001e8,SOC_PORT_BW);
		strings ="SOC:SOCP\t\tRD count" ; //AMON_SOC PORT1: SOCP		 arlen(bytes)
		amon_printf(strings, 0x960002e8,SOC_PORT_BW);
		strings ="SOC:HDLC\t\tRD count" ; //AMON_SOC PORT2: GUACC_HDLC	 arlen(bytes)
		amon_printf(strings, 0x960003e8,SOC_PORT_BW);
		strings ="SOC:IPF\t\tRD count" ; //AMON_SOC PORT3: IPF 		 arlen(bytes)
		amon_printf(strings, 0x960004e8,SOC_PORT_BW);
		strings ="SOC:RSR_ACC\t\tRD count" ; //AMON_SOC PORT4: RSR_ACC 	 arlen(bytes)
		amon_printf(strings, 0x960005e8,SOC_PORT_BW);
		strings ="SOC:SPE\t\tRD count" ; //AMON_SOC PORT5: SPE 		 arlen(bytes)
		amon_printf(strings, 0x960006e8,SOC_PORT_BW);
		strings ="SOC:CS_TMC\t\tRD count" ; //AMON_SOC PORT4: CS_TMC		 arlen(bytes)
		amon_printf(strings, 0x960007e8,SOC_PORT_BW);
		strings ="SOC:AXI2AHB\t\tRD count" ; //AMON_SOC PORT5: AHB2AXI 	 arlen(bytes)
		amon_printf(strings, 0x960008e8,SOC_PORT_BW);
		strings ="SOC:EDMA\t\tWR count" ; //AMON_SOC PORT0: EDMA		 awlen(bytes)
		amon_printf(strings, 0x960001f0,SOC_PORT_BW);
		strings ="SOC:SOCP\t\tWR count" ; //AMON_SOC PORT1: SOCP		 awlen(bytes)
		amon_printf(strings, 0x960002f0,SOC_PORT_BW);
		strings ="SOC:HDLC\t\tWR count" ; //AMON_SOC PORT2: GUACC_HDLC	 awlen(bytes)
		amon_printf(strings, 0x960003f0,SOC_PORT_BW);
		strings ="SOC:IPF\t\tWR count" ; //AMON_SOC PORT3: IPF 		 awlen(bytes)
		amon_printf(strings, 0x960004f0,SOC_PORT_BW);
		strings ="SOC:RSR_ACC\t\tWR count" ; //AMON_SOC PORT4: RSR_ACC 	 awlen(bytes)
		amon_printf(strings, 0x960005f0,SOC_PORT_BW);
		strings ="SOC:SPE\t\tWR count" ; //AMON_SOC PORT5: SPE 		 awlen(bytes) 
		amon_printf(strings, 0x960006f0,SOC_PORT_BW);
		strings ="SOC:CS_TMC\t\tWR count" ; //AMON_SOC PORT4: CS_TMC		 arlen(bytes)
		amon_printf(strings, 0x960007f0,SOC_PORT_BW);
		strings ="SOC:AXI2AHB\t\tWR count" ; //AMON_SOC PORT5: AHB2AXI 	 arlen(bytes) 
		amon_printf(strings, 0x960008f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");

		strings ="MDM:UICC\t\tRD count" ; //AMON_MDM PORT0: UICC		 arlen(bytes)
		amon_printf(strings, 0x804581e8,SOC_PORT_BW);
		strings ="MDM:EDMA\t\tRD count" ; //AMON_MDM PORT1: EDMA		 arlen(bytes)
		amon_printf(strings, 0x804582e8,SOC_PORT_BW);
		strings ="MDM:CIPHER\t\tRD count" ; //AMON_MDM PORT2: CIPHER		 arlen(bytes)
		amon_printf(strings, 0x804583e8,SOC_PORT_BW);
		strings ="MDM:UPACC\t\tRD count" ; //AMON_MDM PORT3: GUACC_UPACC  arlen(bytes)
		amon_printf(strings, 0x804584e8,SOC_PORT_BW);
		strings ="MDM:CICOM0\t\tRD count" ; //AMON_MDM PORT2: GUACC_CICOM0 arlen(bytes)
		amon_printf(strings, 0x804585e8,SOC_PORT_BW);
		strings ="MDM:CICOM1\t\tRD count" ; //AMON_MDM PORT3: GUACC_CICOM1 arlen(bytes)
		amon_printf(strings, 0x804586e8,SOC_PORT_BW);
		strings ="MDM:UICC\t\tWR count" ; //AMON_MDM PORT0: UICC		 awlen(bytes)
		amon_printf(strings, 0x804581f0,SOC_PORT_BW);
		strings ="MDM:EDMA\t\tWR count" ; //AMON_MDM PORT1: EDMA		 awlen(bytes)
		amon_printf(strings, 0x804582f0,SOC_PORT_BW);
		strings ="MDM:CIPHER\t\tWR count" ; //AMON_MDM PORT2: CIPHER		 awlen(bytes)
		amon_printf(strings, 0x804583f0,SOC_PORT_BW);
		strings ="MDM:UPACC\t\tWR count" ; //AMON_MDM PORT3: GUACC_UPACC  awlen(bytes)
		amon_printf(strings, 0x804584f0,SOC_PORT_BW);
		strings ="MDM:CICOM0\t\tWR count" ; //AMON_MDM PORT2: GUACC_CICOM0 awlen(bytes)
		amon_printf(strings, 0x804585f0,SOC_PORT_BW);
		strings ="MDM:CICOM1\t\tWR count" ; //AMON_MDM PORT3: GUACC_CICOM1 awlen(bytes)
		amon_printf(strings, 0x804586f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");
		//////////////////////////////// Phase3. PCIE/BBP monitor
		//------------------------
		//pcie ports
		//------------------------
		//reset
		writel(0x20000000, 0x90000060);
		writel(0x20000000, 0x90000064);
		//amon soft reset
		writel(0x2, 0x96000000);
		//ports cfg
		writel(0xB6D, 0x9600001C);
		//ID cfg
		writel(0x80078040, 0x96000100);
		writel(0x80078050, 0x96000200);
		writel(0x80078060, 0x96000300);
		writel(0x80078070, 0x96000400);
		
		//------------------------
		//bbp ports
		//------------------------	 
		//reset
		writel(0x20000000, 0x80200020);
		writel(0x20000000, 0x80200024);
		//amon soft reset
		writel(0x2, 0x80458000);
		//ports cfg
		writel(0x49, 0x8045801C);
		//ID cfg
		writel(0x800f8040, 0x80458100);
		writel(0x800f8060, 0x80458200);
		writel(0x800f8080, 0x80458300);
		
		//Int. clear
		writel(0xffffffff, 0x96000020);
		writel(0xffffffff, 0x80458020);
		//start amon
		writel(0x00840580, 0x90000800);
		writel(0x00020400, 0x8020040C);    
		
		//waitting for monitor finish
		amon_cnt_flag = 0;
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(300);
			amon_cnt_flag = readl(0x96000008);
		}
		amon_cnt_flag = readl(0x80458008);
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(1);
			amon_cnt_flag = readl(0x80458008);
		}
		writel(0x00840180, 0x90000800);
		writel(0x00020000, 0x8020040C);
		strings ="SOC:PCIE0\t\tRD count"; //AMON_SOC PORT0: PCIE0	  arlen(bytes)
		amon_printf(strings, 0x960001e8,SOC_PORT_BW);
		strings ="SOC:PCIE1\t\tRD count" ; //AMON_SOC PORT1: PCIE1	  arlen(bytes)
		amon_printf(strings, 0x960002e8,SOC_PORT_BW);
		strings ="SOC:USB\t\tRD count" ; //AMON_SOC PORT2: USB3	  arlen(bytes)
		amon_printf(strings, 0x960003e8,SOC_PORT_BW);
		strings ="SOC:GMAC\t\tRD count" ; //AMON_SOC PORT3: GMAC	  arlen(bytes)
		amon_printf(strings, 0x960004e8,SOC_PORT_BW);
		strings ="SOC:PCIE0\t\tWR count" ; //AMON_SOC PORT0: PCIE0	  awlen(bytes)
		amon_printf(strings, 0x960001f0,SOC_PORT_BW);
		strings ="SOC:PCIE1\t\tWR count" ; //AMON_SOC PORT1: PCIE1	  awlen(bytes)
		amon_printf(strings, 0x960002f0,SOC_PORT_BW);
		strings ="SOC:USB3\t\tWR count" ; //AMON_SOC PORT2: USB3	  awlen(bytes)
		amon_printf(strings, 0x960003f0,SOC_PORT_BW);
		strings ="SOC:GMAC\t\tWR count" ; //AMON_SOC PORT3: GMAC	  awlen(bytes)
		amon_printf(strings, 0x960004f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");
		strings ="MDM:BBP_TCM\t\tRD count" ; //AMON_MDM PORT0: BBP_TCM   arlen(bytes)
		amon_printf(strings, 0x804581e8,SOC_PORT_BW);
		strings ="MDM:BBP_DDR\t\tRD count" ; //AMON_MDM PORT1: BBP_DDR   arlen(bytes)
		amon_printf(strings, 0x804582e8,SOC_PORT_BW);
		strings ="MDM:BBE16\t\tRD count" ; //AMON_MDM PORT2: BBE16	  arlen(bytes)
		amon_printf(strings, 0x804583e8,SOC_PORT_BW);
		strings ="MDM:BBP_TCM\t\tWR count" ; //AMON_MDM PORT0: BBP_TCM   awlen(bytes)
		amon_printf(strings, 0x804581f0,SOC_PORT_BW);
		strings ="MDM:BBP_DDR\t\tWR count" ; //AMON_MDM PORT1: BBP_DDR   awlen(bytes)
		amon_printf(strings, 0x804582f0,SOC_PORT_BW);
		strings ="MDM:BBE16\t\tWR count" ; //AMON_MDM PORT2: BBE16	  awlen(bytes)
		amon_printf(strings, 0x804583f0,SOC_PORT_BW);
		printf("--------------------------------------------\n");
		
		writel(0x20000000, 0x90000060);
		writel(0x20000000, 0x90000064);
		writel(0x2, 0x96000000);
		writel(0x2c688, 0x9600001C);
		writel(0x40000000, 0x96000100);
		writel(0x40000000, 0x96000200);
		writel(0x40000000, 0x96000300);
		writel(0x40000000, 0x96000400);
		writel(0x40000000, 0x96000500);
		writel(0x40000000, 0x96000600);
		//amon stop
		writel(0x40000000, 0x96000104);
		writel(0x7fffffff, 0x96000108);
		writel(0x40000000, 0x96000204);
		writel(0x7fffffff, 0x96000208);
		writel(0x40000000, 0x96000304);
		writel(0x7fffffff, 0x96000308);
		writel(0x40000000, 0x96000404);
		writel(0x7fffffff, 0x96000408);
		writel(0x40000000, 0x96000504);
		writel(0x7fffffff, 0x96000508);
		writel(0x40000000, 0x96000604);
		writel(0x7fffffff, 0x96000608);
		writel(0x20000000, 0x80200020);
		writel(0x20000000, 0x80200024);
		writel(0x2, 0x80458000);
		writel(0x2C688, 0x8045801C);
		writel(0x40000000, 0x80458100);
		writel(0x40000000, 0x80458200);
		writel(0x40000000, 0x80458300);
		writel(0x40000000, 0x80458400);
		writel(0x40000000, 0x80458104);
		writel(0x7fffffff, 0x80458108);
		writel(0x40000000, 0x80458204);
		writel(0x7fffffff, 0x80458208);
		writel(0x40000000, 0x80458304);
		writel(0x7fffffff, 0x80458308);
		writel(0x40000000, 0x80458404);
		writel(0x7fffffff, 0x80458408);
		writel(0xffffffff, 0x96000020);
		writel(0xffffffff, 0x80458020);
		writel(0x00840580, 0x90000800);
		writel(0x00020400, 0x8020040C);  
		amon_cnt_flag = 0;
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(300);
			amon_cnt_flag = readl(0x96000008);
		}
		amon_cnt_flag = readl(0x80458008);
		while(0 == (amon_cnt_flag & 0x1))
		{
			osl_task_delay(1);
			amon_cnt_flag = readl(0x80458008);
		}
		writel(0x00840180, 0x90000800);
		writel(0x00020000, 0x8020040C);
		
		strings ="SOC:ACPU_M1\t\tRD count";
		amon_printf_reg(strings, 0x960001e8);			
		strings ="SOC:M3\t\t\tRD count";
		amon_printf_reg(strings, 0x960002e8);
		strings = "SOC:ACPU_M0\t\tRD count";  //AMON_SOC PORT2: ACPU_M0  arlen(bytes)
		amon_printf_reg(strings, 0x960003e8);		
		strings ="SOC:HIFI\t\tRD count";      //AMON_SOC PORT3: HIFI	 arlen(bytes)
		amon_printf_reg(strings, 0x960004e8);
		strings ="SOC:PERI_MST\t\tRD count" ; //AMON_SOC PORT4: PERI_MST arlen(bytes)
		amon_printf_reg(strings, 0x960005e8);
		strings ="SOC:PCIE_BRG\t\tRD count" ; //AMON_SOC PORT5: PCIE_BRG arlen(bytes)
		amon_printf_reg(strings, 0x960006e8);
		strings ="SOC:ACPU_M1\t\tWR count" ;  //AMON_SOC PORT0: ACPU_M1:awlen(bytes)
																	
		amon_printf_reg(strings, 0x960001f0);
		strings ="SOC:M3\t\t\tWR count" ;     //AMON_SOC PORT1: M3 awlen(bytes)
		amon_printf_reg(strings, 0x960002f0);
		strings ="SOC:ACPU_M0\t\tWR count" ;  //AMON_SOC PORT2: ACPU_M0  awlen(bytes)
		amon_printf_reg(strings, 0x960003f0);
		strings ="SOC:HIFI\t\tWR count" ;     //AMON_SOC PORT3: HIFI	 awlen(bytes)
		amon_printf_reg(strings, 0x960004f0);
		strings ="SOC:PERI_MST\t\tWR count" ; //AMON_SOC PORT4: PERI_MST awlen(bytes)
		amon_printf_reg(strings, 0x960005f0);
		strings ="SOC:PCIE_BRG\t\tWR count" ; //AMON_SOC PORT5: PCIE_BRG awlen(bytes)	
		amon_printf_reg(strings, 0x960006f0);
        u64 am1_rd_suml = readl(0x960001e8) ;
		u64 soc_rd_suml = readl(0x960002e8) + readl(0x960003e8) +\
			              readl(0x960004e8) + readl(0x960005e8) + readl(0x960006e8);
		u64 am1_rd_sumh = readl(0x960001ec) ;
        u64 soc_rd_sumh = readl(0x960002ec) + readl(0x960003ec) +\
	                      readl(0x960004ec) + readl(0x960005ec) + readl(0x960006ec);
        u64 am1_wr_suml = readl(0x960001f0) ;
        u64 soc_wr_suml = readl(0x960002f0) + readl(0x960003f0) +\
			              readl(0x960004f0) + readl(0x960005f0) + readl(0x960006f0);
        u64 am1_wr_sumh = readl(0x960001f4) ;
        u64 soc_wr_sumh = readl(0x960002f4) + readl(0x960003f4) +\
	                      readl(0x960004f4) + readl(0x960005f4) + readl(0x960006f4);
		soc_rd_sumh += soc_rd_suml>>32;
		soc_wr_sumh += soc_wr_suml>>32;
		printf("SOC to DDR Read  high: 0x%x\tlow:0x%x\n",(u32)soc_rd_sumh,(u32)soc_rd_suml);
		printf("SOC to DDR Write high: 0x%x\tlow:0x%x\n",(u32)soc_wr_sumh,(u32)soc_wr_suml);		
		printf("AM1 to DDR Read  high: 0x%x\tlow:0x%x\n",(u32)am1_rd_sumh,(u32)am1_rd_suml);
		printf("AM1 to DDR Write high: 0x%x\tlow:0x%x\n",(u32)am1_wr_sumh,(u32)am1_wr_suml);
		printf("--------------------------------------------\n");
		strings ="MDM:CCPU_M1\t\tRD count" ; //AMON_MDM PORT0: CCPU_M1  arlen(bytes)
		amon_printf_reg(strings, 0x804581e8);
		strings ="MDM:BBP_BRG\t\tRD count" ; //AMON_MDM PORT1: BBP_BRG  arlen(bytes)
		amon_printf_reg(strings, 0x804582e8);
		strings ="MDM:ACPU_M0\t\tRD count" ; //AMON_MDM PORT2: CCPU_M0  arlen(bytes)
		amon_printf_reg(strings, 0x804583e8);
		strings ="MDM:PERI_MST\t\tRD count"; //AMON_MDM PORT3: PERI_MST arlen(bytes)
		amon_printf_reg(strings, 0x804584e8);
		strings ="MDM:CCPU_M1\t\tWR count" ; //AMON_MDM PORT0: CCPU_M1  awlen(bytes)
		amon_printf_reg(strings, 0x804581f0);
		strings ="MDM:BBP_BRG\t\tWR count" ; //AMON_MDM PORT1: BBP_BRG  awlen(bytes)
		amon_printf_reg(strings, 0x804582f0);
		strings ="MDM:CCPU_M0\t\tWR count" ; //AMON_MDM PORT2: CCPU_M0  awlen(bytes)
		amon_printf_reg(strings, 0x804583f0);
		strings ="MDM:PERI_MST\t\tWR count" ; //AMON_MDM PORT3: PERI_MST awlen(bytes)
		amon_printf_reg(strings, 0x804584f0);
        u64 cm1_rd_suml= readl(0x804581e8) ;
        u64 mdm_rd_suml= readl(0x804582e8) + readl(0x804583e8) + readl(0x804584e8);
																
        u64 cm1_rd_sumh= readl(0x804581ec) ;
        u64 mdm_rd_sumh= readl(0x804582ec) + readl(0x804583ec) + readl(0x804584ec);
		mdm_rd_sumh += mdm_rd_suml>>32;
        u64 cm1_wr_suml= readl(0x804581f0) ;
        u64 mdm_wr_suml= readl(0x804582f0) + readl(0x804583f0) + readl(0x804584f0);
        u64 cm1_wr_sumh= readl(0x804581f4) ;
        u64 mdm_wr_sumh= readl(0x804582f4) + readl(0x804583f4) + readl(0x804584f4);		
		mdm_wr_sumh += mdm_wr_suml>>32;
		printf("MDM to DDR Read  high: 0x%x\tlow:0x%x\n",(u32)mdm_rd_sumh,(u32)mdm_rd_suml);
		printf("MDM to DDR write high: 0x%x\tlow:0x%x\n",(u32)mdm_wr_sumh,(u32)mdm_wr_suml);
		printf("CM1 to DDR Read  high: 0x%x\tlow:0x%x\n",(u32)cm1_rd_sumh,(u32)cm1_rd_suml);
		printf("CM1 to DDR write high: 0x%x\tlow:0x%x\n",(u32)cm1_wr_sumh,(u32)cm1_wr_suml);
        u64    rd_sumsoc = (mdm_rd_sumh<<32) + (soc_rd_sumh<<32) + mdm_rd_suml + soc_rd_suml;
		double rd_divsoc = ((double)rd_sumsoc/SOC_PORT_BW)*100;
        u64    wr_sumsoc = (mdm_wr_sumh<<32) + (soc_wr_sumh<<32) + mdm_wr_suml + soc_wr_suml;
		double wr_divsoc = ((double)wr_sumsoc/SOC_PORT_BW)*100;
        u64    rd_sum_m1 = (cm1_rd_sumh<<32) + (am1_rd_sumh<<32) + cm1_rd_suml + am1_rd_suml;
		double rd_div_m1 = ((double)rd_sum_m1/M1_PORT_BW)*100;
        u64    wr_sum_m1 = (cm1_wr_sumh<<32) + (am1_wr_sumh<<32) + cm1_wr_suml + am1_wr_suml;
		double wr_div_m1 = ((double)wr_sum_m1/M1_PORT_BW)*100;
		printf("MST_M1_2DDR read usage is:%3.4f,\t write usage is:%3.4f\n",rd_div_m1,wr_div_m1);
		printf("MST_SOC2DDR read usage is:%3.4f,\t write usage is:%3.4f\n",rd_divsoc,wr_divsoc);
		printf("--------------------------------------------\n");
		printf("\n\n");

    }
}
BSP_S32 busstress_amon_status_start(void)
{
	return osl_task_init("amon show",g_amon_priority,0x2000,(OSL_TASK_FUNC)bsp_amonitor_show,NULL,&g_amon_taskid);
}
/*bus stress test switch*/
BSP_S32 busstress_test_start(int task_priority)
{

	/*open upacc\cicom\amon clk*/
	writel(0x00400900,0x80200000);
	writel(0x00000018,0x90000000);
		
	if(0 != acc_stress_test_start(task_priority, 0, cipher_stress_test_rate))
	    printf("ccore acc stress test0 fail\n");
	
#ifdef CONFIG_PSAM
	if(0 != psam_dl_stress_test_start(task_priority, stress_test_rate))
		printf("ccore psam non_st dl stress test fail\n");
	if(0 != psam_cipher_dl_stress_test_start(task_priority, stress_test_rate))
		printf("ccore psam cipher st dl stress test fail\n");
#else
	if(0 != ipf_dl_stress_test_start(task_priority, stress_test_rate))
	    printf("ccore ipf dl stress test fail\n");
#endif

	if(0 != a9_mem_stress_test_start_use_bbe16(stress_test_rate))
	    printf("ccore use bbe16 stress test fail\n",0,0,0,0,0,0);

	if(0 != a9_mem_stress_test_start_use_ddr(stress_test_rate))
	    printf("ccore use bbe16 stress test fail\n",0,0,0,0,0,0);
	if(0 != a9_mem_stress_test_start_use_aximem64(stress_test_rate))
	    printf("ccore use aximem64 stress test fail\n");
	
	if(-1 == gu_master_stress_test_start(task_priority,stress_test_rate))
	    printf("gu_master_stress_test_start stress test fail\n");
	
	if(busstress_amon_status_start())
	    printf("star amon show task fail!\n");
    /* edma16_xx : mdm edma */
	edma_test_lli_loop_ddr(EDMA_SCI0_RX); /* edma16_10 ,16*/
	edma_test_lli_loop_sram(EDMA_SCI1_RX); /* edma16_11,18*/


    /* edma4_xx : soc edma */
	edma_test_lli_loop_ddr(EDMA_LTESIO_RX); /* edma4_4, 4*/
#if (defined(BSP_CONFIG_EMU_ZEBU) || defined(BSP_CONFIG_EMU_PALADIN))
	edma_test_lli_loop_sram(EDMA_LTESIO_TX);/* edma4_5 ,5 */
#endif

	return OK;
}

BSP_S32 busstress_test_stop(void)
{
	if(0 != edma_stress_test_stop())
	    printf("ccore edma stress test stop fail\n");

	if(0 != acc_stress_test_stop())
	    printf("ccore acc stress test0 stop fail\n");

#ifdef CONFIG_PSAM
	if(0 != psam_dl_stress_test_stop())
	    printf("ccore psam dl non_st stress test fail\n");
	if(0 != psam_cipher_dl_stress_test_stop())
	    printf("ccore psam dl cipher st stress test fail\n");
#else
	if(0 != ipf_dl_stress_test_stop())
	    printf("ccore ipf dl stress test fail\n");
#endif

	if(0 != a9_mem_stress_test_stop_use_bbe16())
	    printf("ccore use bbe16 stress test fail\n",0,0,0,0,0,0);

	if(0 != a9_mem_stress_test_stop_use_hifi())
	    printf("ccore use hifi stress test fail\n",0,0,0,0,0,0);

	if(0 != a9_mem_stress_test_stop_use_aximem64())
	    printf("ccore use aximem64 stress test fail\n");
	
	if(0 != gu_master_stress_test_stop())
	    printf("gu_master_stress_test_stop stress test fail\n");

	return OK;
}



