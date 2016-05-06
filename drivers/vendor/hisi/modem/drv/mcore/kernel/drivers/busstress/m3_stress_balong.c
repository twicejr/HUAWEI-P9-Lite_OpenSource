#include <cmsis_os.h>
#include "product_config.h"
#include "osl_malloc.h"
#include "osl_types.h"
#include "bsp_om.h"
#include "drv_comm.h"
#include "bsp_busstress.h"
#include "bsp_hardtimer.h"

#define  printf(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_STRESS, "[M3 strss test]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

void m3_memcpy_ddr_testcace(void const *obj);
void m3_memcpy_srm_testcase(void const *obj);

static osThreadId  g_ddr_taskid = 0;
osThreadDef(m3_memcpy_ddr_testcace, osPriorityNormal, 1, 512);
osThreadDef(m3_memcpy_srm_testcase, osPriorityNormal, 1, 512);
//extern osStatus osDelay(u32);

/*test process*/
/* RAND_MAX assumed to be 32767 */
#if (defined(BSP_CONFIG_EMU_ZEBU) || defined(BSP_CONFIG_EMU_PALADIN))
static osThreadId  g_srm_taskid = 0;
#endif
static unsigned long next          = 1;
static int myrand(void) {
   next = next * 1103515245 + 12345;
   return((unsigned)(next/65536) % 32768);
}

static void mysrand(unsigned seed) {
   next = seed;
}

int memcpy_test_process(void * src_addr,void* dst_addr,unsigned int size)
{
	int ret = 0;

	mysrand((unsigned)src_addr);
	memset(src_addr,myrand(),size);
	memset(dst_addr,0,size);
	memcpy(dst_addr,src_addr,size);
	ret = memcmp(src_addr,dst_addr,size);
	if(0 != ret )
	{
		printk("memcmp fail,iRet:0x%x\n",ret);
		return ret;
	}

	return 0;
}
void m3_memcpy_ddr_testcace(void const *obj)
{
	void *       src_addr = NULL;
	void *       dst_addr = NULL;
	unsigned int size     = M3_DATA_CACHE_SIZE / 2;
	unsigned int count    = 0;

	src_addr = (void *)M3_DDR_BASEADDR;

	dst_addr = (void *)(M3_DDR_BASEADDR + size);	

	for( ; ; ){

		if(memcpy_test_process(src_addr,dst_addr,size)){
			printf("memcpy_test_process failed!\n");
		}

		osDelay(1);
		if(0 == (++count % 10000)){
			printf("m3 memcpy use ddr test count is %d\n",count);
		}

	}

}
void m3_memcpy_srm_testcase(void const *obj)
{
	void *       src_addr = NULL;
	void *       dst_addr = NULL;
	unsigned int size     = AXI_MEM_FOR_MEMCPY_SIZE;
	unsigned int count    = 0;
	int          ret      = 0;

	src_addr = (void *)AXI_MEM_64_SRC_FOR_MCORE;

	dst_addr = (void *)AXI_MEM_64_DST_FOR_MCORE;	

	for( ; ; ){
		ret = memcpy_test_process(src_addr,dst_addr,size);
		if(ret){
			printf("memcpy_test_process failed!\n");
		}
		
		osDelay(1);
		if(0 == (++count % 10000)){
			printf("m3 memcpy use srm test count is %d\n",count);
		}
	}

}


/*bus stress test switch*/
int busstress_test_start(void)
{
	g_ddr_taskid = osThreadCreate(osThread(m3_memcpy_ddr_testcace), NULL);
	if(NULL == g_ddr_taskid){
		printf("ddr test task create failed !\n");
		return -1;
	}
#if (defined(BSP_CONFIG_EMU_ZEBU) || defined(BSP_CONFIG_EMU_PALADIN))
	g_srm_taskid = osThreadCreate(osThread(m3_memcpy_srm_testcase), NULL);
	if(NULL == g_srm_taskid){
		printf("sram test task create failed !\n");
		return -1;
	}
#endif
	return OK;
}

int busstress_test_stop(void)
{
	osThreadTerminate(g_ddr_taskid);
#if (defined(BSP_CONFIG_EMU_ZEBU) || defined(BSP_CONFIG_EMU_PALADIN))
	osThreadTerminate(g_srm_taskid);
#endif
	return 0;
}

