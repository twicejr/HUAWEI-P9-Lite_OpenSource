#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include "pmu_balong.h"
#include "pmu_pmic.h"
#include "pmu_fpga.h"

/*****************************************************************************
 函 数 名  : dummy_pmu_init
 功能描述  : 初始化默认打桩函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : LED模块
*****************************************************************************/
void dummy_pmu_init(void)
{
    pmu_print_error("no pmic macro defined,use dummy!\n");
}
/*****************************************************************************
 函 数 名  : dummy_info_get_handler
 功能描述  : 查询PMU版本号的打桩函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
u32 dummy_info_get_handler(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return  0;
}
char* dummy_version_get(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return NULL;
}
int dummy_sim_upres_disable(u32 para)
{
    pmu_print_info("no pmic macro defined,use dummy!\n",para);
    return  0;
}
void dummy_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    pmu_print_info("no pmic macro defined,use dummy,para is %d,%d!\n",dcxoId,value);
}
void dummy_rfclk_onoff(u32 para)
{
    pmu_print_info("no pmic macro defined,use dummy,para is %d!\n",para);
}
int dummy_get_rfclk_status(u32 rfid)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}

u32 dummy_get_rtc_value(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}
int dummy_ocp_register(int volt_id,PMU_OCP_FUNCPTR func)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}

struct pmu_adp_ops g_pmu_adpops = {
    .version_get = dummy_version_get,
    .sim_upres_disable = dummy_sim_upres_disable,
    .dcxo_compensate = dummy_dcxo_compensate,
    .rfclk_enable = dummy_rfclk_onoff,
    .rfclk_disable = dummy_rfclk_onoff,
    .rfclk_is_enabled = dummy_get_rfclk_status,
    .get_rtc_value = dummy_get_rtc_value,
    .ocp_register = dummy_ocp_register,
};

int pmu_adpops_register(struct pmu_adp_ops *pmic_ops)
{
    if (NULL == pmic_ops)
    {
        pmu_print_error("argc is NULL check it\n");
        return BSP_ERROR;
    }
    g_pmu_adpops = *pmic_ops;

    return BSP_OK;
}

/*以下函数只在Ccore\Mcore和FASTBOOT中提供*/
/*****************************************************************************
 函 数 名  : bsp_pmu_init
 功能描述  :系统启动初始化pmu相关信号量
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :ccore系统初始化函数
*****************************************************************************/
void bsp_pmu_init(void)
{
#if defined(CONFIG_PMIC_FPGA)
    pmu_fpga_init();
#endif

#ifdef CONFIG_PMU_NEW
    pmu_pmic_init();
    pmu_dcdc_init();
#endif
}

/*----------------------------------基本寄存器操作接口---------------------------------------*/
/*****************************************************************************
* 函 数 名  : bsp_pmic_get_base_addr
*
* 功能描述  : 返回pmu基地址
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : pmu初始化之前为0，初始化之后是映射后的基址
*****************************************************************************/
#ifdef CONFIG_PMU_NEW
u32 bsp_pmic_get_base_addr(void)
{
    return pmic_get_base_addr();
}
void bsp_pmic_reg_write(u32 addr, u32 value)
{
    pmic_reg_write(addr, value);
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
void bsp_pmic_reg_read(u32 addr, u32 *pValue)
{
    pmic_reg_read(addr, pValue);
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
void bsp_pmic_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    pmic_reg_write_mask(addr, value, mask);
}
int bsp_pmic_reg_show(u32 addr)
{
    return pmic_reg_show(addr);
}
#else
u32 bsp_pmic_get_base_addr(void)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}
void bsp_pmic_reg_write(u32 addr, u32 value)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
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
void  bsp_pmic_reg_read(u32 addr, u32 *pValue)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
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
void bsp_pmic_reg_write_mask(u32 addr, u32 value, u32 mask)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
}
int bsp_pmic_reg_show(u32 addr)
{
    pmu_print_info("no pmic macro defined,use dummy!\n");
    return 0;
}
#endif

/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取pmu版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : 集成hso，msp调用
*****************************************************************************/
char* bsp_pmu_version_get(void)
{
    return g_pmu_adpops.version_get();
}
/*****************************************************************************
*  函 数 名  : mdrv_pmu_dcxo_fre_compensate
*  功能描述  : 为dcxo设置频率补偿
*  输入参数  : value:需要设置的值
*
*  输出参数  : 无
*  返 回 值  : null
*
******************************************************************************/
void bsp_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
#ifdef CONFIG_PMIC_FPGA
    pmic_dcxo_compensate(dcxoId,value);
#else
    g_pmu_adpops.dcxo_compensate(dcxoId,value);
#endif
}
void bsp_pmu_rfclk_enable(u32 rf_id)
{
    g_pmu_adpops.rfclk_enable(rf_id);
}
void bsp_pmu_rfclk_disable(u32 rf_id)
{
    g_pmu_adpops.rfclk_disable(rf_id);
}
int bsp_pmu_rfclk_is_enabled(u32 rf_id)
{
    return g_pmu_adpops.rfclk_is_enabled(rf_id);
}
int bsp_pmu_ocp_register(int volt_id,PMU_OCP_FUNCPTR func)
{
    return g_pmu_adpops.ocp_register(volt_id,func);
}
#ifdef CONFIG_AVOID_RFIC6362_LDO27_LEAK
int mdrv_pmu_set_ldo27_ao(int ao)
{
	return pmic_set_ldo27_ao(ao);
}
#endif
