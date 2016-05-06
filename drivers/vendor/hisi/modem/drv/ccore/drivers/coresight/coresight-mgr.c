/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  Coresight_mgr.c
*
*   作    者 :  l00169177
*
*   描    述 :  coresight驱动管理
*
*   修改记录 :  2014年10月24日  v1.00  l00169177  创建
*************************************************************************/
#include <stdio.h>
#include "coresight-platform.h"
#include "bsp_dump.h"
#include "bsp_coresight.h"
#include "bsp_nvim.h"
#include "osl_common.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "coresight-dep.h"
#include "securec.h"

/*lint --e{801, 830, 570, 534, 586, 522}*/

/* tmc memory address in dump */
 u8* g_tmc_dump_addr = 0;

/* tmc memory length in dump */
 u32 g_tmc_dump_len  = 0;

/* coresight enable flag */
u32 g_cs_enable = false;

/* coresight suspend flag */
u32 g_cs_suspend = false;

extern u32 coresight_tmc_data_addr;
extern u32 coresight_tmc_data_len;
extern int coresight_etm_init(void);
extern int coresight_funnel_init(void);
extern int coresight_tmc_init(void);
extern int coresight_platform_init(void);
extern int coresight_etm_cpu_enable(unsigned int cpu);
extern void coresight_etm_cpu_disable(unsigned int cpu);

/* coresight enable */
void bsp_coresight_enable(void)
{
	if(dump_get_product_type() == DUMP_PHONE)
	{
		if(coresight_get_dep_status() != BSP_OK)
		{
			cs_error("coresight dep reg can not access\n");
			return;
		}
	}

    coresight_etm_cpu_enable(CP_CORE_SET);
}

/* coresight disable */
void bsp_coresight_disable(void)
{
	if(dump_get_product_type() == DUMP_PHONE)
	{
		if(coresight_get_dep_status() != BSP_OK)
		{
			cs_error("coresight dep reg can not access\n");
			return;
		}
	}
    coresight_etm_cpu_disable(CP_CORE_SET);
}

/* coresight callback function for dump */
unsigned int bsp_coresight_dump_callback(void)
{
    bsp_coresight_disable();

    if(!coresight_tmc_data_addr || !coresight_tmc_data_len)
    {
        cs_error("bsp_coresight_dump_callback: no data in tmc.\n");
        return BSP_OK;
    }

    if(coresight_tmc_data_len > g_tmc_dump_len)
    {
        cs_error("bsp_coresight_dump_callback error: DUMP UTRACE SIZE too small.\n");
        return BSP_ERROR;
    }

    if(*((u32 *)g_tmc_dump_addr) != CORESIGHT_MAGIC_NUM)
    {
        /* the first four bytes for magic number */
        *((u32 *)g_tmc_dump_addr) = (u32)CORESIGHT_MAGIC_NUM;
        /* tht second four bytes for tmc data length */
        *((u32 *)g_tmc_dump_addr + 1) = coresight_tmc_data_len;

        memcpy_s((u32*)g_tmc_dump_addr+2, coresight_tmc_data_len, (void*)coresight_tmc_data_addr, coresight_tmc_data_len);
        //cs_error("save coresight TMC data to dump OK.\n");
    }

    return BSP_OK;
}

/* coresight intialization */
unsigned int bsp_coresight_init()
{
    dump_handle handle;
    NV_DUMP_STRU    dump_nv;

    /* read dump NV */
    if(BSP_OK != bsp_nvm_read(NVID_DUMP, (u8 *)&dump_nv, sizeof(NV_DUMP_STRU)))
    {
        cs_error("read nv %d fail\n", NVID_DUMP);
        return BSP_ERROR;
    }

    /* judge coresight enable set */
    if(dump_nv.traceOnstartFlag != 1)
    {
        cs_error( "trace not enable\n");
        return BSP_OK;
    }

    /* register field in dump  */
    if(dump_nv.traceCoreSet & (1<<CP_CORE_SET))
    {
        g_tmc_dump_addr = (u8*)bsp_dump_register_field(DUMP_CP_UTRACE, "CP_CORESIGHT",
                                        0, 0, DUMP_CP_UTRACE_SIZE, 0);
        if(BSP_NULL == g_tmc_dump_addr)
        {
            cs_error( "get dump buffer fail\n");
            return BSP_ERROR;
        }
        g_tmc_dump_len = DUMP_CP_UTRACE_SIZE;
        memset_s(g_tmc_dump_addr, g_tmc_dump_len, 0, g_tmc_dump_len);
    }
    else
    {
        cs_error( "CP trace is not set\n");
        return BSP_OK;
    }

    /* register dump callback */
    handle = bsp_dump_register_hook("CP_CORESIGHT", (dump_hook)bsp_coresight_dump_callback);
    if((handle == BSP_ERROR) ||(handle==(dump_handle)NULL))/*lint !e830*/
    {
        cs_error( "dump register fail\n");
        return BSP_ERROR;
    }
	if(dump_get_product_type() == DUMP_PHONE)/*lint !e539*/
	{
		if(coresight_get_dep_cfg() != BSP_OK)
		{
			return BSP_ERROR;
		}
	}
	/*coresight platform init*/
    if(coresight_platform_init() != BSP_OK)
        return BSP_ERROR;

    /* tmc initialization */
    if(coresight_tmc_init() != BSP_OK)
        return BSP_ERROR;

    /* funnel initialization */
    if(coresight_funnel_init() != BSP_OK)
        return BSP_ERROR;

    /* etm initialization */
    if(coresight_etm_init() != BSP_OK)
        return BSP_ERROR;

    /* enable etm and coresight */
    bsp_coresight_enable();

    g_cs_enable = true;

    cs_error( "init ok\n");
    return 0;
}


void bsp_coresight_suspend(void)
{
    if(g_cs_enable == false)
    {
        return;
    }
    g_cs_suspend = true;
    bsp_coresight_disable();
}

void bsp_coresight_resume(void)
{
    if(g_cs_enable == false)
    {
        return;
    }
    g_cs_suspend = false;
    bsp_coresight_enable();
}

