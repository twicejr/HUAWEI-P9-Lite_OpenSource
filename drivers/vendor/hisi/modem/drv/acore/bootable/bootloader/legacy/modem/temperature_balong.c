

#ifdef __cplusplus
extern "C" {
#endif
#include <product_config.h>
#include <mdrv_temp_cfg.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_shared_ddr.h>
#include "nv_boot.h"
/*lint -save -e801 -e838 -e835*/

#ifndef TEMPERATURE_OK
#define TEMPERATURE_OK                   0
#endif

#ifndef TEMPERATURE_ERROR
#define TEMPERATURE_ERROR                -1
#endif

#ifndef TEMPERATURE_MAGIC_DATA
#define TEMPERATURE_MAGIC_DATA           0x5A5A5A5A
#endif

#ifdef CONFIG_TEMPERATURE_PROTECT
int tem_protect_nv_config(void)
{
    TEMP_HKADC_CHAN_CONFIG chan_cfg[HKADC_CHAN_MAX];
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE);
    unsigned int i = 0;
    unsigned int ret = 0;
    unsigned int nv_id = 0;
    unsigned int length = 0;
    /* 共享内存初始化为0 */
    memset(p_area, 0, (u32)sizeof(DRV_HKADC_DATA_AREA));

	/* HKADC的配置NV */
    memset(chan_cfg, 0, (u32)(HKADC_CHAN_MAX * sizeof(TEMP_HKADC_CHAN_CONFIG)));
	ret = bsp_nvm_read(NV_ID_DRV_TEMP_HKADC_CONFIG,(u8*)&chan_cfg, (u32)(HKADC_CHAN_MAX * sizeof(TEMP_HKADC_CHAN_CONFIG)));
	if(0 != ret)
	{
		cprintf("bsp_nvm_readpart fail, nv id 0x%x, ret = 0x%x.\n", NV_ID_DRV_TEMP_HKADC_CONFIG, ret);
		goto nv_hkadc_error;
	}

	/* 把读到的NV内容，配置到共享内存中，并根据NV的配置，读取对应的温度转换表 */
    for(i = 0; i < HKADC_CHAN_MAX; i++)
    {
        p_area->chan_cfg[i].outcfg.out_config= chan_cfg[i].out_config;
        p_area->chan_cfg[i].have_config= chan_cfg[i].have_config;
        p_area->chan_cfg[i].out_peroid= chan_cfg[i].out_period;
        p_area->chan_cfg[i].temp_data_len= chan_cfg[i].convert_list_len;

        length = p_area->chan_cfg[i].temp_data_len;
        /*lint -save -e734 -e571*/
        nv_id  = (unsigned int)(chan_cfg[i].convert_list_id);
        /*lint -restore*/

        if(0 != nv_id && (0 != length))
        {
        	ret = bsp_nvm_read(nv_id, (u8*)(p_area->chan_cfg[i].temp_table), (u32)(sizeof(TEM_VOLT_TABLE) * length));
            if(0 != ret)
            {
				cprintf("bsp_nvm_read fail, nv id 0x%x, ret = 0x%x.\n", nv_id, ret);
                goto nv_hkadc_error;
            }
        }
    }

	/* 读HKADC物理通道和逻辑通道对应关系的NV */
	ret = bsp_nvm_read(NV_ID_DRV_TEMP_CHAN_MAP, (u8*)(p_area->phy_tbl), (u32)sizeof(TEMP_HKADC_PHY_LOGIC_ARRAY));
    if(0 != ret)
    {
		cprintf("bsp_nvm_read fail, nv id 0x%x, ret = 0x%x.\n", NV_ID_DRV_TEMP_CHAN_MAP, ret);
        goto nv_hkadc_error;
    }

	/* 设置flag，表示成功 */
    p_area->magic_start = TEMPERATURE_MAGIC_DATA;
    p_area->magic_end = TEMPERATURE_MAGIC_DATA;
    return TEMPERATURE_OK;

nv_hkadc_error:
    return TEMPERATURE_ERROR;
}


void bsp_temperature_init(void)
{
    /* 从NV里面获取温保基本信息保存到共享内存 */
	int ret = tem_protect_nv_config();
    if(TEMPERATURE_OK != ret)
    {
        cprintf("tem_protect_nv_config fail, ret = %d.\n", ret);
		goto error;
    }

	/* 初始化成功 */
	cprintf("temperature init ok\n");
	return;

error:
	cprintf("temperature init error\n");
	return;
}
#else

void bsp_temperature_init(void)
{
	cprintf("temperature init stub\n");
	return;
}
#endif
/*lint -restore*/
#ifdef __cplusplus
}
#endif
