#include <product_config.h>
#include <osl_bio.h>
#include <osl_malloc.h>
#include <soc_memmap.h>
#include <libfdt.h>
#include <bsp_shared_ddr.h>

#include <bsp_pm_om.h>
#include <bsp_hardtimer.h>
#include <bsp_pmu.h>
#include <bsp_version.h>
#include <hi_pmu.h>

#define  pmu_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  pmu_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct pmu_ops_strc
{
    void (*pmu_init)(void);
};
static u32 pmic_base_addr;

/*----------------------------------基本寄存器操作接口---------------------------------------*/
void pmic_reg_write(u32 addr, u32 value)
{
    writel(value,(pmic_base_addr + (addr << 2)));
}
/*****************************************************************************
* 函 数 名  : pmu_reg_read
*
* 功能描述  : 对pmu芯片寄存器的读函数
*
* 输入参数  : u16 addr：待写入的寄存器地址
*             u8 u8Data：读出的数据
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void  pmic_reg_read(u32 addr, u32 *pValue)
{
    *pValue = readl(pmic_base_addr + (addr << 2));
}
/*****************************************************************************
* 函 数 名  : pmu_reg_write_mask
*
* 功能描述  : 对pmu芯片寄存器的某些bit置位
*
* 输入参数  : u16 addr：待写入的寄存器地址
*             u8 u8Data：读出的数据
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void pmic_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    u32 reg_tmp = 0;

    pmic_reg_read(addr, &reg_tmp);
    reg_tmp &= ~mask;
    reg_tmp |= value;
    pmic_reg_write(addr, reg_tmp);
}
int pmic_reg_show(u32 addr)
{
    u32 value = 0;

    pmic_reg_read(addr, &value);
    pmu_print_error("pmuRead addr 0x%x value is 0x%x!!\n",addr,value);
    return (int)value;
}

s32 bsp_pmu_suspend(void)
{
    u32 pmu_version = 0;
	/* 配置OUT_PMUA电源进入ECO */
	pmic_reg_write(0x0A2, 0x01);
	
	/* 配置THERMAL 模块Ref_top进入ECO */
	//pmic_reg_write_mask(0x0AA, 0x1, 0x1);
	
	/* 配置0x117寄存器锁解除 */
	pmic_reg_write(0x117, 0x6c);
	/* 配置xo_core_en的使能信号置高，xo_ldo_en使能信号置低 */
	pmic_reg_write(0x10B, 0x04);

    pmic_reg_read( 5, &pmu_version);
    if( 0x20 == pmu_version ) /* pmu version v520*/
    {
        /* buck2给ldo32供电。
           在 ldo32 给 ddrphy_IO 供电方案下，需要在 ddr进自刷新/ldo32下电之后关闭buck2
           所以这里不关 buck2  */
    }
    else
    {
    	/* 配置buck2 关闭 */
    	pmic_reg_write_mask(0x09c, 0x0, 0x2);
    }
    return 0;
}
s32 bsp_pmu_resume(void)
{

    u32 pmu_version = 0;

    pmic_reg_read( 5, &pmu_version);
    if( 0x20 == pmu_version ) /* pmu version v520*/
    {
        /* buck2给ldo32供电。
           在 ldo32 给 ddrphy_IO 供电方案下，需要在 ddr进自刷新/ldo32下电之后关闭buck2
           ddr 上电之前 打开 buck2 和 ldo32
           所以这里不开 buck2  */
    }
    else
    {
    	/* 配置buck2 打开 */
    	pmic_reg_write_mask(0x09c, 0x2, 0x2);
    }

	
	/* 配置xo_core_en的使能信号置低，xo_ldo_en使能信号置高 */
	pmic_reg_write(0x10B, 0x07);
	/* 配置0x117寄存器锁 */
	pmic_reg_write(0x117, 0x00);
	

	/* 配置THERMAL 模块Ref_top退出ECO */
	//pmic_reg_write_mask(0x0AA, 0x0, 0x1);

	/* 配置OUT_PMUA电源退出ECO */
	pmic_reg_write(0x0A2, 0x00);
    return 0;
}

s32 bsp_pmu_sdio_suspend(void)
{
    return 0;
}
s32 bsp_pmu_sdio_resume(void)
{
    return 0;
}
#if 0

/*查询pmu每一路实际的开关状态给低功耗调用*/
void bsp_pmu_volt_state_save(void)
{
    return;
}
u8 bsp_pmu_version_get(void)
{
    return 0;
}
#endif
void bsp_pmu_init(void)
{
	pmic_base_addr = PMIC_BASE_ADDR;
    printk("\npmu init\n");
    return;
}

