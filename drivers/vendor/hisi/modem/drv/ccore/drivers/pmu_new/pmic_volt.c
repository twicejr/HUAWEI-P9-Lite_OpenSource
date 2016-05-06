/*
 * pmu_hi6559.c -- simple synchronous userspace interface to SSI devices
 *
 * Copyright (C) 2006 SWAPP
 *  Andrea Paterniani <a.paterniani@swapp-eng.it>
 * Copyright (C) 2007 David Brownell (simplification, cleanup)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*lint --e{537,958}*/
#include <string.h>
#include <of.h>
#include <securec.h>
#include <osl_bio.h>
#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>
#include <soc_memmap.h>
#include <bsp_shared_ddr.h>
#include <bsp_pmu.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_version.h>
#include <bsp_nvim.h>
#include <bsp_ipc.h>
#include <bsp_regulator.h>
#include <bsp_pm_om.h>

#include <pmu_balong.h>
#include <pmu_pmic.h>

struct pmic_volt_info g_pmic_voltinfo;
/*****************************************************************************
* 函 数 名  : pmic_volt_para_check
*
* 功能描述  : 检查电压源是否合法
*
* 输入参数  : @volt_id：待检查的电压源
*
* 输出参数  : 无
*
* 返 回 值  : BSP_PMU_OK:合法;   BSP_PMU_ERROR:不合法
*****************************************************************************/
static __inline__ int pmic_volt_para_check(int volt_id)
{
    /* 有效性检查 */
    if ((g_pmic_voltinfo.volt_max< volt_id) || (g_pmic_voltinfo.volt_min> volt_id))
    {
        pmu_print_error("PMIC doesn't have volt %d!\n",volt_id);
        pmu_print_error("the volt you can use in this PMIC is from %d to %d,please check!\n", g_pmic_voltinfo.volt_min, g_pmic_voltinfo.volt_max);
        return BSP_PMU_ERROR;
    }

    return BSP_PMU_OK;
}

/*****************************************************************************
* 函 数 名  : pmic_volt_table_check
*
* 功能描述  : 检查电压源属性表是否存在
*
* 输入参数  : @pmic_volt_table 电压源属性表地址
*
* 输出参数  : 无
*
* 返 回 值  : BSP_PMU_OK:存在;   BSP_PMU_ERROR:不存在
*****************************************************************************/
static __inline__ int pmic_volt_table_check(void)
{
    if((SHM_PMU_VOLTTABLE_MAGIC_START_DATA == g_pmic_voltinfo.magic_start) &&
       (SHM_PMU_VOLTTABLE_MAGIC_END_DATA == g_pmic_voltinfo.magic_end))
    {
        return BSP_PMU_OK;
    }

    return BSP_PMU_ERROR;
}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_enable
 功能描述  : 使能电源volt_id
 输入参数  : @volt_id 电源id
 输出参数  : 无
 返 回 值  : BSP_PMU_OK: 成功； else:失败
*****************************************************************************/
int pmic_volt_enable(int volt_id)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
	unsigned long volt_flag = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = (struct pmic_volt_ctrl*)(&g_pmic_voltinfo.volt_ctrl[volt_id]);
    /* keep a distance of off_on_delay from last time disabled */

    /*故核间锁+核内锁*/
    spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
    /* cannot enable more than one regulator at one time */
    /* set enable register */
    pmic_reg_write_mask(volt_ctrl->volt_reg.en_reg,((u32)0x1 << volt_ctrl->volt_reg.en_bit),((u32)0x1 << volt_ctrl->volt_reg.en_bit));
    spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);

    return iret;

}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_disable
 功能描述  : 禁止电源volt_id
 输入参数  : @volt_id 电源id
 输出参数  : 无
 返 回 值  : BSP_PMU_OK: 成功； else:失败
*****************************************************************************/
int pmic_volt_disable(int volt_id)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
	unsigned long volt_flag = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = (struct pmic_volt_ctrl*)(&g_pmic_voltinfo.volt_ctrl[volt_id]);
    /* keep a distance of off_on_delay from last time disabled */

    /*故核间锁+核内锁*/
    spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
    /* set disable register */
    pmic_reg_write_mask(volt_ctrl->volt_reg.en_reg,((u32)0x0 << volt_ctrl->volt_reg.en_bit),((u32)0x1 << volt_ctrl->volt_reg.en_bit));
    spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);

    return BSP_PMU_OK;

}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_is_enabled
 功能描述  : 查询某路电压源是否开启。
 输入参数  : volt_id:电压源id号
 输出参数  : 无
 返 回 值  : 0:未开启；else:开启
*****************************************************************************/
int pmic_volt_is_enabled(int volt_id)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
    u32 regval = 0;
	unsigned long volt_flag = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = (struct pmic_volt_ctrl*)(&g_pmic_voltinfo.volt_ctrl[volt_id]);
    /* keep a distance of off_on_delay from last time disabled */

    spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
    pmic_reg_read(volt_ctrl->volt_reg.state_reg,&regval);
    spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);

    /* 开关状态bit为1时，表示已使能 */
    return (int)(regval & ((u32)0x1 << volt_ctrl->volt_reg.state_bit));
}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_get_voltage
 功能描述  : 获取电压源volt_id的电压值
 输入参数  : volt_id:电压源id号
 输出参数  : 无
 返 回 值  : 电压值
*****************************************************************************/
int pmic_volt_get_voltage(int volt_id)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
    u32 regval = 0;
    u32 vsel = 0;
    u32 voltage = 0;
	unsigned long volt_flag = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];

    if(volt_ctrl->voltage_flag == VOLT_TABLE)/*若是档位，则查询*/
    {
        spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
        pmic_reg_read(volt_ctrl->volt_reg.voltage_reg, &regval);
        spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);
        /* 获取电压档位值 */
        vsel = (regval & volt_ctrl->volt_reg.voltage_mask);
        voltage = volt_ctrl->voltage_table[vsel];
    }
    else if(volt_ctrl->voltage_flag == VOLT_LINEAR)/*若是线性，则计算*/
    {
        spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
        pmic_reg_read(volt_ctrl->volt_reg.voltage_reg, &regval);
        spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);
        /* 获取电压档位值 */
        vsel = (regval & volt_ctrl->volt_reg.voltage_mask);
        voltage = volt_ctrl->voltage_base + vsel * volt_ctrl->voltage_step;
    }
    else /*若是恒定电压，不能改变，返回恒定*/
    {
        voltage = volt_ctrl->voltage_const;
    }

    pmu_print_info("volt_id %d's voltage is  %d uV!\n", volt_id, voltage);

    return (int)voltage;
}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_set_voltage
 功能描述  : 设置电压源volt_id的电压值，配置为[min_uV, max_uV]区间的值即可，如果区间内没有合法值，失败返回
 输入参数  : volt_id: 要设置的电源编号
             min_uV: 最小合法电压值
             max_uV: 最大合法电压值
 输出参数  : @selector: 实际设置电压值的档位
 返 回 值  : BSP_PMU_OK: 成功； else:失败
*****************************************************************************/
int pmic_volt_set_voltage(int volt_id, int min_uV, int max_uV,unsigned *selector)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    pmic_voltflags_t flags = 0;
    int iret = BSP_PMU_OK;
    u32 vsel = 0;
    u32 voltage = 0;
	unsigned long volt_flag = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];

    if(volt_ctrl->voltage_flag == 0)/*若是档位，则查询*/
    {


        for(vsel = 0; vsel < volt_ctrl->voltage_nums; vsel++)
        {
            if (((u32)min_uV <= volt_ctrl->voltage_table[vsel]) && ((u32)max_uV >= volt_ctrl->voltage_table[vsel]))
            {
                break;
            }
        }
        if((vsel == volt_ctrl->voltage_nums))
        {
            pmu_print_error("volt_id %d cann't support voltage between %d and %d uV!\n",volt_id,min_uV,max_uV);
            return BSP_PMU_ERROR;
        }
        *selector = vsel;
        voltage = volt_ctrl->voltage_table[vsel];

        spin_lock_irqsave(&volt_ctrl->volt_lock, volt_flag);
        pmic_reg_write_mask(volt_ctrl->volt_reg.voltage_reg, vsel, volt_ctrl->volt_reg.voltage_mask);
        spin_unlock_irqrestore(&volt_ctrl->volt_lock, volt_flag);

		/*lint -save -e801*/
        goto out;
		/*lint -restore*/
    }
    else if(volt_ctrl->voltage_flag == 1)/*若是线性，则计算*/
    {
        for(vsel = 0; vsel < volt_ctrl->voltage_nums; vsel++)
        {
            if(((u32)min_uV <= (volt_ctrl->voltage_base + vsel * volt_ctrl->voltage_step)) && ((u32)max_uV >= (volt_ctrl->voltage_base + vsel * volt_ctrl->voltage_step)))
            {
                break;
            }
        }
        if(vsel == volt_ctrl->voltage_nums)
        {
            pmu_print_error("volt_id %d cann't support voltage between %d and %d uV!\n",volt_id,min_uV,max_uV);
            return BSP_PMU_ERROR;
        }
        *selector = vsel;
        voltage = volt_ctrl->voltage_base + vsel * volt_ctrl->voltage_step;

        spin_lock_irqsave(&volt_ctrl->volt_lock,flags);
        pmic_reg_write_mask(volt_ctrl->volt_reg.voltage_reg, vsel, volt_ctrl->volt_reg.voltage_mask);
        spin_unlock_irqrestore(&volt_ctrl->volt_lock,flags);

		/*lint -save -e801*/
        goto out;
		/*lint -restore*/
    }
    else /*若是恒定电压，不能改变*/
    {
        if(((u32)min_uV <= volt_ctrl->voltage_const)&&((u32)max_uV >= volt_ctrl->voltage_const))
        {
            voltage = volt_ctrl->voltage_const;
			/*lint -save -e801*/
            goto out;
			/*lint -restore*/
        }
        else
        {
            pmu_print_error("volt_id %d's voltage can not be set!\n", volt_id);
            return BSP_PMU_ERROR;
        }
    }

out:
    pmu_print_info("voltage is set at %d uV!\n", voltage);
    return BSP_PMU_OK;

}

/*****************************************************************************
 函 数 名  : bsp_pmic_volt_list_voltage
 功能描述  : 获取电压源volt_id档位为selector的电压值
 输入参数  : volt_id: 要设置的电源编号
             selector: 电压档位
 返 回 值  : BSP_PMU_OK: 成功； else:失败
*****************************************************************************/
int pmic_volt_list_voltage(int volt_id, unsigned selector)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
    u32 voltage = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }

    volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];

    /* 检查档位有效性 */
    if (selector >= volt_ctrl->voltage_nums)
    {
        pmu_print_error("selector is %d,not exist,-EINVAL,please input new\n", selector);
        return BSP_PMU_ERROR;
    }

    if(volt_ctrl->voltage_flag == 0)/*若是档位，则查询*/
    {
        voltage = volt_ctrl->voltage_table[selector];
    }
    else if(volt_ctrl->voltage_flag == 1)/*若是线性，则计算*/
    {
        voltage = volt_ctrl->voltage_base + selector * volt_ctrl->voltage_step;
    }
    else /*若是恒定电压，不能改变，返回恒定*/
    {
        voltage = volt_ctrl->voltage_const;
    }


    pmu_print_info("volt %d selector %d is %d uV!!\n",volt_id,selector,voltage);

    return (int)voltage;

}
/*****************************************************************************
 函 数 名  : bsp_pmic_volt_list_show
 功能描述  : 显示当前所需路电源的所有档位值
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void pmic_volt_list_show(int volt_id)
{
    struct pmic_volt_ctrl* volt_ctrl = NULL;
    int iret = BSP_PMU_OK;
    u32 selector = 0;
    int voltage = 0;

    /* 参数有效性检查 */
    iret = pmic_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return;
    }

    /* 电压属性表安全性检查 */
    iret = pmic_volt_table_check();
    if(BSP_PMU_OK != iret)
    {
        return;
    }

    volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];

    for(selector = 0;selector < volt_ctrl->voltage_nums;selector++)
    {
        voltage = pmic_volt_list_voltage(volt_id,selector);
        pmu_print_error("volt %d selector %d is %d uV!!\n",volt_id,selector,voltage);
    }

    return;
}

struct regulator_id_ops pmic_volt_ops = {
        .list_voltage = pmic_volt_list_voltage,
        .set_voltage = pmic_volt_set_voltage,
        .get_voltage = pmic_volt_get_voltage,
        .is_enabled = pmic_volt_is_enabled,
        .enable = pmic_volt_enable,
        .disable = pmic_volt_disable,
};
void pmic_register_ops(void)
{
    int ret = 0;

    ret = regulator_pmic_ops_register(&pmic_volt_ops, "pmic");
    if (ret)
    {
        pmu_print_error("register pmic_ops ops failed\n");
    }

}

/*****************************************************************************
 函 数 名  : bsp_pmu_pmic_init
 功能描述  : PMIC pmic PMU模块初始化
 输入参数  : 无
 输出参数  : 无
*****************************************************************************/
void pmic_volt_init(void)
{
    /*read dts*/
    pmic_volt_dts_init();

    g_pmic_voltinfo.magic_start = SHM_PMU_VOLTTABLE_MAGIC_START_DATA;
    g_pmic_voltinfo.magic_end = SHM_PMU_VOLTTABLE_MAGIC_END_DATA;

    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_ASIC)
    {
        pmic_register_ops();
    }
    pmic_ocp_init();

    pmu_print_error("pmic volt init ok!\n");
}
