

#ifdef __cplusplus
extern "C"
{
#endif
#include <osl_bio.h>
#include <hi_syscrg_interface.h>
#include <hi_syssc_interface.h>
#include <bsp_sysctrl.h>
#include "amon_balong.h"
#include "printk.h"
#include "bsp_version.h"
#include <libfdt.h>

/* 备份恢复数据 */
axi_reg_bak_t * g_st_reg_bak = NULL;
/* 掉电前运行标志 */
u32 g_ul_running[2] = {false, false};
u32 g_ul_bak_flag[2] = {false, false};
u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT] = {};
struct amon_sysctrl_struct g_amon_sysctrl;

static void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value)
{
    /* 根据配置目标读取相应寄存器 */
    switch(config)
    {
        /* 读取CPUFAST寄存器 */
        case AXI_CPUFAST_CONFIG:
            *value = readl(AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* 读取SOC寄存器 */
        case AXI_SOC_CONFIG:
            *value = readl(AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}


static void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value)
{
    /* 根据配置目标写入相应寄存器 */
    switch(config)
    {
        /* 写CPUFAST寄存器 */
        case AXI_CPUFAST_CONFIG:
            writel(value, AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* 写SOC寄存器 */
        case AXI_SOC_CONFIG:
            writel(value, AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}


static u32 axi_is_clk_enable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        return amon_cpufast_get_clk_status();
    }

    if(AXI_SOC_CONFIG == config)
    {
        return amon_soc_get_clk_status();
    }

    return 1;
}


static void axi_clk_enable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_clk_enable();
    }

    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_clk_enable();
    }
}


static void axi_clk_disable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_clk_disable();
    }

    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_clk_disable();
    }
}


static axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config)
{
    u32 reg_value = 0;

    /* 从状态寄存器获取运行状态 */
    axi_reg_read(config, AXI_MON_CNT_STATE_INT, &reg_value);

    return reg_value & 0xC;
}


static void axi_reset(axi_config_enum_uint32 config)
{
    /* 软复位 */
    axi_reg_write(config, AXI_MON_CNT_RESET, 0x2);
}


static void axi_sc_mon_start(axi_config_enum_uint32 config)
{
    /* 启动CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_start();
    }
    /* 启动SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_start();
    }
    else
    {
        return;
    }
}


static void axi_sc_mon_stop(axi_config_enum_uint32 config)
{
    /* 停止CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_stop();
    }
    /* 停止SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_stop();
    }
    else
    {
        return;
    }
}


void bsp_amon_suspend()
{
    u32 i;
    u32 j;
    u32 reg_value;
    /*lint -save -e958*/
    unsigned long long data_cnt;
    /*lint -restore*/
    u32 data_low;
    u32 data_high;
    axi_state_enum_uint32 state;
    u32 clk_status;
    axi_reg_bak_t * reg_bak;

    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        reg_bak = &g_st_reg_bak[i];
        clk_status = axi_is_clk_enable(i);
        if(!clk_status)
        {
            axi_clk_enable(i);
        }

        state = axi_get_state(i);
        if(AXI_UNWIN_RUNNING != state)
        {
            g_ul_running[i] = false;

            if(!clk_status)
            {
                axi_clk_disable(i);
            }

            continue;
        }

        /* 备份前，先停止monitor */
        axi_sc_mon_stop(i);
        g_ul_running[i] = true;

        /* 控制寄存器备份 */
        axi_reg_read(i, AXI_MON_CNT_CTRL, &(reg_bak->ctrl_reg));
        axi_reg_read(i, AXI_MON_PORT_SEL, &(reg_bak->port_reg));
        axi_reg_read(i, AXI_ID_INT_MASK, &(reg_bak->int_mask));
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_read(i, AXI_MON_CNT_ID(j), &(reg_bak->id_reg[j]));
            axi_reg_read(i, AXI_MON_ID_ADDR_DES(j), &(reg_bak->addr_start_reg[j]));
            axi_reg_read(i, AXI_MON_ID_ADDR_DES_M(j), &(reg_bak->addr_end_reg[j]));
        }

        /* 第一次下电，清空备份区 */
        if(g_ul_bak_flag[i] == false)
        {
            g_ul_bak_flag[i] = true;
            for(j=0; j<AXI_MAX_CONFIG_ID; j++)
            {
                reg_bak->incr1_reg[j] = 0;
                reg_bak->incr2_reg[j] = 0;
                reg_bak->incr4_reg[j] = 0;
                reg_bak->incr16_reg[j] = 0;
                reg_bak->wrap_reg[j] = 0;
                reg_bak->burst_send_reg[j] = 0;
                reg_bak->burst_fin_reg[j] = 0;
                reg_bak->rd_cnt_high_reg[j] = 0;
                reg_bak->rd_cnt_low_reg[j] = 0;
                reg_bak->wr_cnt_high_reg[j] = 0;
                reg_bak->wr_cnt_low_reg[j] = 0;
            }
        }

        /* 统计寄存器累加 */
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_read(i, AXI_MON_INCR1_ID(j), &reg_value);
            reg_bak->incr1_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR2_ID(j), &reg_value);
            reg_bak->incr2_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR4_ID(j), &reg_value);
            reg_bak->incr4_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR8_ID(j), &reg_value);
            reg_bak->incr8_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR16_ID(j), &reg_value);
            reg_bak->incr16_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_WRAP_ID(j), &reg_value);
            reg_bak->wrap_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_BURST_ID(j), &reg_value);
            reg_bak->burst_send_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_FINISH_ID(j), &reg_value);
            reg_bak->burst_fin_reg[j] += reg_value;
            /* 读写数据总量40bit长度，需要计算溢出值 */
            axi_reg_read(i, AXI_MON_RD_BYTES_ID_LOW(j), &data_low);
            axi_reg_read(i, AXI_MON_RD_BYTES_ID_HIGH(j), &data_high);
            data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->rd_cnt_low_reg[j];
            reg_bak->rd_cnt_high_reg[j] += data_high;
            if(data_cnt >> 32)
            {
                reg_bak->rd_cnt_high_reg[j] += 1;
            }
            reg_bak->rd_cnt_low_reg[j] = (u32)data_cnt;
            axi_reg_read(i, AXI_MON_WR_BYTES_ID_LOW(j), &data_low);
            axi_reg_read(i, AXI_MON_WR_BYTES_ID_HIGH(j), &data_high);
            data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->wr_cnt_low_reg[j];
            reg_bak->wr_cnt_high_reg[j] += data_high;
            if(data_cnt >> 32)
            {
                reg_bak->wr_cnt_high_reg[j] += 1;
            }
            reg_bak->wr_cnt_low_reg[j] = (u32)data_cnt;
        }

        if(!clk_status)
        {
            axi_clk_disable(i);
        }
    }
}


void bsp_amon_resume()
{
    u32 i;
    u32 j;
    u32 clk_status;
    axi_reg_bak_t * reg_bak;



    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        /* 掉电前monitor未运行，不执行恢复操作 */
        if(false == g_ul_running[i])
        {
            continue;
        }

        reg_bak = &g_st_reg_bak[i];
        clk_status = axi_is_clk_enable(i);
        if(!clk_status)
        {
            axi_clk_enable(i);
        }

        axi_reset(i);

        axi_reg_write(i, AXI_MON_CNT_CTRL, reg_bak->ctrl_reg);
        axi_reg_write(i, AXI_MON_PORT_SEL, reg_bak->port_reg);
        axi_reg_write(i, AXI_ID_INT_MASK, reg_bak->int_mask);
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_write(i, AXI_MON_CNT_ID(j), reg_bak->id_reg[j]);
            axi_reg_write(i, AXI_MON_ID_ADDR_DES(j), reg_bak->addr_start_reg[j]);
            axi_reg_write(i, AXI_MON_ID_ADDR_DES_M(j), reg_bak->addr_end_reg[j]);
        }

        /* 启动monitor */
        axi_sc_mon_start(i);

        if(!clk_status)
        {
            axi_clk_disable(i);
        }
    }
}
s32 axi_init(void)
{
	struct device_node dev[AXI_CTRL_ADDR_BUTT] = {};
    struct device_node *node = NULL;
    char *reg_name[amon_soc_dts_butt] = {"amon_clk_en", "amon_clk_dis", "amon_clk_status", "amon_start", "dw_clk_en",
										"dw_clk_dis", "dw_clk_status"};
    u32 i = 0;
    u32 reg_addr[3] = {};

    /* 备份恢复数据 */
    g_st_reg_bak = (axi_reg_bak_t *)AXI_MON_BACK_ADDR;

    node = of_find_compatible_node(NULL, NULL, "hisilicon,amon_fast2_balong");
    if(node)
    {
        dev[AXI_FAST_ADDR_ENUM].offset = node->offset;
    }
    node = of_find_compatible_node(NULL, NULL, "hisilicon,amon_soc2_balong");
    if(node)
    {
        dev[AXI_SOC_ADDR_ENUM].offset = node->offset;
    }

	if((0 == dev[AXI_FAST_ADDR_ENUM].offset)||(0 == dev[AXI_SOC_ADDR_ENUM].offset))
	{
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: read dts error\n", __FUNCTION__);
		return BSP_ERROR;
	}
	g_amon_base_addr[AXI_FAST_ADDR_ENUM] = (u32)of_iomap(&dev[AXI_FAST_ADDR_ENUM], 0);
	g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(&dev[AXI_SOC_ADDR_ENUM], 0);

	if ((0 == g_amon_base_addr[AXI_FAST_ADDR_ENUM])||(0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM]))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "remap amon fail\n fast base addr = 0x%x slow base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
		return BSP_ERROR;
	}

    /*SOC相关系统控制器信息初始化*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(&dev[AXI_SOC_ADDR_ENUM], reg_name[i], reg_addr, 3))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "get soc dts fail\n");
            return BSP_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
    /*cpu fast相关系统控制器信息初始化*/
    for(i = 0; i < amon_cpufast_dts_butt; i++)
    {
        if(of_property_read_u32_array(&dev[AXI_FAST_ADDR_ENUM], reg_name[i], reg_addr, 3))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "get fast dts fail\n");
            return BSP_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_fast[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_fast[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_fast[i].end_bit = reg_addr[AMON_END_BIT];
    }


    return BSP_OK;
}


#ifdef __cplusplus
}
#endif


