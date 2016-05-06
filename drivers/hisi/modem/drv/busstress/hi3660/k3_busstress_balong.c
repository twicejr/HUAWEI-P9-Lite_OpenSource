#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include "drv_comm.h"
#include "mdrv_memory.h"
#include "bsp_busstress.h"
#include <bsp_hardtimer.h>
#include "bsp_ipf.h"

BSP_S32 stress_test_rate = 2;
extern BSP_S32 SOCP_ST_ENCODE_STRESS(void);
extern BSP_S32 SOCP_ST_DECODE_STRESS(void);
extern BSP_S32 ipf_ul_stress_test_start(BSP_S32 task_priority);
extern BSP_VOID ipf_ul_stress_test_stop();

unsigned int busstress_ddr_memcpy_count = 0;
int busstress_ddr_memcpy_delay = 10;
bool busstress_ddr_memcpy_run  = false;
int g_busstress_show_bandwidth_delay = 60000; /* 60000ms,1min */

int busstress_memcpy_threadfunc(void* data)
{
    void* pSrcAddr = NULL;
    void* pDstAddr = NULL;

    int delay =  *((int*)data);

    pSrcAddr = kmalloc(DDR_MEM_SIZE_FOR_AP, GFP_KERNEL);
    if(NULL == pSrcAddr)
    {
        return ERROR;
    }

    pDstAddr = kmalloc(DDR_MEM_SIZE_FOR_AP, GFP_KERNEL);
    if(NULL == pDstAddr)
    {
        kfree(pSrcAddr);
        return ERROR;
    }

    while(busstress_ddr_memcpy_run)
	{
		if(0 != memcpyTestProcess(pSrcAddr, pDstAddr, DDR_MEM_SIZE_FOR_AP))
		{
			printk("busstress_ddr_memcpy_stress_test failed.\n");
			break;
		}

        //dma_map_single(NULL, pSrcAddr, s32Size, DMA_TO_DEVICE);
	    //dma_map_single(NULL, pDstAddr, s32Size, DMA_TO_DEVICE);

		busstress_ddr_memcpy_count++;
		if(0 == (busstress_ddr_memcpy_count%5))
		{
			msleep(delay);
		}
	}

    kfree(pSrcAddr);
    kfree(pDstAddr);

	return BSP_OK;
}

void busstress_ddr_memcpy_test_start(int delay)
{
    busstress_ddr_memcpy_delay = delay;
    busstress_ddr_memcpy_run   = true;
    kthread_run(busstress_memcpy_threadfunc, &busstress_ddr_memcpy_delay, "ddrmemcpytask", 0, 0);
}

void busstress_ddr_memcpy_test_stop()
{
    busstress_ddr_memcpy_run   = false;
    busstress_ddr_memcpy_count = 0;
}

void busstress_info_print()
{
    printk("ddr_memcpy_test info begin:\n");
    printk("busstress_ddr_memcpy_count = %d\n", busstress_ddr_memcpy_count);
    printk("busstress_ddr_memcpy_delay = %d\n", busstress_ddr_memcpy_delay);
    printk("busstress_ddr_memcpy_run   = %d\n", busstress_ddr_memcpy_run);
    printk("ddr_memcpy_test info end:\n");
}

enum busstress_module_no{
	BUSSTRESS_TEST_IPF,                      /* 0 */
	BUSSTRESS_TEST_SOCP,                     /* 1 */
	BUSSTRESS_TEST_AP,                       /* 2 */
	BUSSTRESS_TEST_BUTTOM
};

unsigned int g_busstress_test_en_run[BUSSTRESS_TEST_BUTTOM] =
{
	1,	/* BUSSTRESS_TEST_IPF 					  */
	1,	/* BUSSTRESS_TEST_SOCP				      */
	1 	/* BUSSTRESS_TEST_AP					  */
};


static unsigned int g_print_cnt = 0;

struct ap_memcpy_bandwidth{
	unsigned int slice_delta;  /* 此次统计使用的slice，单位: 1/32768 秒 */
	unsigned int bytes_delta;  /* 此次的数据量，单位:字节 */
};

#define AP_MEMCPY_CNT_MAX   1500
struct ap_memcpy_bandwidth g_ap_memcpy_bandwidth[AP_MEMCPY_CNT_MAX];

int busstress_ap_memcpy_bandwidth_threadfunc(void* data)
{
    unsigned int memcpy_cnt_start = 0;
	unsigned int memcpy_cnt_end = 0;
	unsigned int memcpy_start_slice = 0;
	unsigned int memcpy_end_slice = 0;
	unsigned int cnt_delta = 0;
	unsigned int bytes_delta = 0;
	unsigned int slice_delta = 0;

    int delay =  *((int*)data);

    for ( ; ; )
	{

	    memcpy_cnt_start = busstress_ddr_memcpy_count;
		memcpy_start_slice = bsp_get_slice_value();
		msleep(delay);
		memcpy_cnt_end = busstress_ddr_memcpy_count;
		memcpy_end_slice = bsp_get_slice_value();
		slice_delta = get_timer_slice_delta(memcpy_start_slice, memcpy_end_slice);
		g_ap_memcpy_bandwidth[g_print_cnt % AP_MEMCPY_CNT_MAX].slice_delta = slice_delta;

		printk("-----------------ap print_cnt=%d\n", g_print_cnt);
		printk("-----------------ap memcpy slice_delta %d \n", slice_delta);

		/* 计算带宽 */
		cnt_delta = memcpy_cnt_end - memcpy_cnt_start;
		bytes_delta = cnt_delta * DDR_MEM_SIZE_FOR_AP;
		g_ap_memcpy_bandwidth[g_print_cnt % AP_MEMCPY_CNT_MAX].bytes_delta = bytes_delta;

		printk("-----------------ap memcpy bytes_delta %d \n", bytes_delta);


		g_print_cnt++;

	}



    return 0;
}

int busstress_ap_memcpy_bandwidth_show(void)
{
    unsigned int i = 0;

	for (i = 0; i < g_print_cnt; i++)
	{
		printk("cnt %04d slice_delta %d bytes_delta %d\n", i, g_ap_memcpy_bandwidth[i % AP_MEMCPY_CNT_MAX].slice_delta,
			                                                g_ap_memcpy_bandwidth[i % AP_MEMCPY_CNT_MAX].bytes_delta);
	}

    return 0;
}

int memcpyTestProcess(void* pSrcAddr, void* pDstAddr, int iSize)
{
	int iRet = 0;

	memset((void*)pSrcAddr, 0,iSize);

	/* ddr->ddr 申请的就是不可cache的内存 */
	//(void)osl_cache_flush(OSL_DATA_CACHE, (void *)pSrcAddr, iSize); /* 从cache冲出 */

	memset((void*)pDstAddr, 0,     iSize);
	/* ddr->ddr 申请的就是不可cache的内存 */
	//(void)osl_cache_flush(OSL_DATA_CACHE, (void *)pDstAddr, iSize); /* 从cache冲出 */

	memcpy((void*)pDstAddr, (void*)pSrcAddr, iSize);
	/* ddr->ddr 申请的就是不可cache的内存 */
	//(void)osl_cache_invalid(OSL_DATA_CACHE, (void *)pSrcAddr, iSize);
	//(void)osl_cache_invalid(OSL_DATA_CACHE, (void *)pDstAddr, iSize);

    return iRet;
}

BSP_S32 busstress_test_start(void)
{

	int ret = 0;

	/* IPF */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_IPF])
	{
		//(void)ipf_dl_stress_test_start();
		ipf_ul_stress_test_start(stress_test_rate);
		printk("acore ipf busstress test start ++++++ok\n");
	}
	else
	{
		printk("acore ipf busstress test no run******\n");
	}

    /* SOCP */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_SOCP])
	{
		//ret = SOCP_ST_ENCODE_STRESS();
		ret = SOCP_ST_BUSSTRESS_TEST();
		if (0 != ret)
		{
			printk("acore socp busstress test start ------fail\n");
		}
		else
		{
			printk("acore socp busstress test start ++++++ok\n");
		}
	}
	else
	{
		printk("acore socp busstress test no run******\n");
	}

#if 0
	if(0 != SOCP_ST_DECODE_STRESS())
        printk("acore socp decode stress test fail\n");
#endif

    /* ap */
	if (1 == g_busstress_test_en_run[BUSSTRESS_TEST_AP])
	{
		busstress_ddr_memcpy_test_start(stress_test_rate);
		printk("ap busstress test start ++++++ok\n");
	}
	else
	{
		printk("ap busstress test no run******\n");
	}


	/* 起任务，打印带宽 */
    kthread_run(busstress_ap_memcpy_bandwidth_threadfunc, &g_busstress_show_bandwidth_delay, "ShowApBandWidth", 0, 0);
	return OK;
}

BSP_S32 busstress_test_stop(void)
{
	ipf_ul_stress_test_stop();
    busstress_ddr_memcpy_test_stop();

	return OK;
}

void busstress_moudle_open(enum busstress_module_no moudle)
{
    g_busstress_test_en_run[moudle] = 1;
}
void busstress_moudle_close(enum busstress_module_no moudle)
{
    g_busstress_test_en_run[moudle] = 0;
}

