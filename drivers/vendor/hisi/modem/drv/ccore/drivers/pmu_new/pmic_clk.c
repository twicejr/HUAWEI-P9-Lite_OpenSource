/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  clk_balong.c
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  clk ops
*
*   修改记录 : 2014年9月15日  v1.00  h00277960  创建
**************************************************************************/

/*lint --e{530,525,628,666,801,830} */

#include <string.h>
#include <securec.h>
#include <osl_types.h>
#include <osl_thread.h>
#include <osl_malloc.h>
#include <of.h>
#include <bsp_clk.h>
#include <pmu_pmic.h>
#include <bsp_slice.h>
#include <bsp_ipc.h>
#include <pmu_balong.h>

#ifndef BIT
#define BIT(nr)			(1UL << (nr))
#endif

#define CLK_SET_RATE_PARENT	     BIT(2) /* 频率改变时，向父时钟蔓延一级 */
#define CLK_IGNORE_UNUSED	     BIT(3) /* 不使用也不关断 */

struct pmic_clk {
	struct  clk_hw	             hw;
	unsigned long                rate;
    u32                          en_dis_offset;
    u32                          en_dis_bit;
    u32                          freq_addr_offset;
    u32                          freq_mask;
    u32                          delay_us;
};

extern struct clk *drv_clk_register(const char * ptr_device, struct clk_hw *ptr_clk_hw);
extern void drv_clkdev_add(struct clk_lookup *ptr_clk_lookup);

static char *pmic_alloc_copy(const char *src_str)
{
	unsigned int len;
	char         *dst_str = NULL;

	if (!src_str)
	{
		return NULL;
	}

	len = strlen(src_str) + 1;
	dst_str = osl_malloc(len);
	if (dst_str)
	{
		(void)memcpy_s(dst_str, len, src_str, len);
	}

	return dst_str;
}

extern struct pmic_xo_info g_pmic_xoinfo;
extern void pmic_mutli_core_lock(void);
extern void pmic_mutli_core_unlock(void);

static int pmic_clk_enable(struct clk_hw *hw)
{
	struct pmic_clk *clk_pmic = container_of(hw, struct pmic_clk, hw);
    u32    reg_val = 0;
    unsigned long rfclk_flag = 0;

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock, rfclk_flag);
    /* 打开前写0 */
    pmic_reg_read(clk_pmic->freq_addr_offset, &reg_val);
    reg_val &= (~(clk_pmic->freq_mask));
    pmic_reg_write(clk_pmic->freq_addr_offset, reg_val);

    /*enable clk*/
    pmic_mutli_core_lock();

    pmic_reg_read(clk_pmic->en_dis_offset, &reg_val);
    reg_val |= (((u32)0x1) << clk_pmic->en_dis_bit);
    pmic_reg_write(clk_pmic->en_dis_offset, reg_val);

    pmic_mutli_core_unlock();
    /*delay 6us*/
    udelay(clk_pmic->delay_us);

    /* 打开后写1 */
    pmic_reg_read(clk_pmic->freq_addr_offset, &reg_val);
    reg_val |= clk_pmic->freq_mask;
    pmic_reg_write(clk_pmic->freq_addr_offset, reg_val);

    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock, rfclk_flag);

    return 0;
}

static void pmic_clk_disable(struct clk_hw *hw)
{
	struct pmic_clk *clk_pmic = container_of(hw, struct pmic_clk, hw);
    u32    reg_val = 0;
    unsigned long rfclk_flag = 0;

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock, rfclk_flag);
    pmic_mutli_core_lock();

    pmic_reg_read(clk_pmic->en_dis_offset, &reg_val);
    reg_val &= (~(((u32)0x1) << clk_pmic->en_dis_bit));
    pmic_reg_write(clk_pmic->en_dis_offset, reg_val);

    pmic_mutli_core_unlock();
    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock, rfclk_flag);
}

static int pmic_clk_is_enabled(struct clk_hw *hw)
{
	struct pmic_clk *clk_pmic = container_of(hw, struct pmic_clk, hw);
    u32    reg_val = 0;
    unsigned long rfclk_flag = 0;

    spin_lock_irqsave(&g_pmic_xoinfo.xorf_lock, rfclk_flag);
    pmic_mutli_core_lock();

    pmic_reg_read(clk_pmic->en_dis_offset, &reg_val);
    reg_val &= ((u32)1 << clk_pmic->en_dis_bit);

    pmic_mutli_core_unlock();
    spin_unlock_irqrestore(&g_pmic_xoinfo.xorf_lock, rfclk_flag);

    return reg_val ? 1 : 0;
}


static struct clk_ops g_pmic_clk_ops = {
	.enable		= pmic_clk_enable,
	.disable	= pmic_clk_disable,
	.is_enabled = pmic_clk_is_enabled,
};

static void pmic_clk_setup(struct device_node *node)
{
    struct clk_init_data *init = NULL;
    struct clk *pclk = NULL;
    struct pmic_clk *clk_pmic = NULL;
    const char *clk_name;
    struct device_node *child_node = NULL;
    const char *parent_names = "tcxo";
    u32   data[2] = {0};
	struct clk_lookup    *ptr_clk_lookup = NULL;
    u32   freq_cfg[3] = {0};


	for_each_available_child_of_node(node, child_node)
	{
        if (of_property_read_string(child_node, "clock-output-names", &clk_name))
        {
            pmu_print_error("node %s doesn't have clock-output-name property!\n", child_node->name);
            return ;
        }

        if (of_property_read_u32_array(child_node, "reg_offset_bit", &data[0], 2))
        {
            pmu_print_error("node %s doesn't have reg_offset_bit property!\n", child_node->name);
            return ;
        }

        if (of_property_read_u32_array(child_node, "freq_cfg", &freq_cfg[0], 3))
        {
            pmu_print_error("node %s doesn't have freq_cfg property!\n", child_node->name);
            return ;
        }

        pmu_print_error("clk_name %s\n", clk_name);
        clk_pmic = osl_malloc(sizeof(struct pmic_clk));
        if (!clk_pmic)
        {
            pmu_print_error("[%s] fail to alloc clk_pmic!\n", __func__);
            goto err_pmic_clk;
        }



        init = osl_malloc(sizeof(struct clk_init_data));
        if (!init)
        {
            pmu_print_error("malloc init err\n");
            goto err_init;
        }

        init->name = pmic_alloc_copy(clk_name);
        init->ops = &g_pmic_clk_ops;
        init->flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED;
        init->parent_names = &parent_names;
        init->num_parents = 1;

        clk_pmic->hw.init = init;

        clk_pmic->en_dis_offset = data[0];
        clk_pmic->en_dis_bit = data[1];
        clk_pmic->freq_addr_offset = freq_cfg[0];
        clk_pmic->freq_mask = freq_cfg[1];
        clk_pmic->delay_us = freq_cfg[2];


        pclk = drv_clk_register(NULL, &clk_pmic->hw);
        if (IS_ERR(pclk))
        {
            pmu_print_error("drv_clk_register ERR\n");
            goto err_register;
        }

        ptr_clk_lookup = osl_malloc(sizeof(struct clk_lookup));
        if (IS_ERR(ptr_clk_lookup))
        {
             pmu_print_error("clk %s fail to malloc clk_lookup\n", pclk->name);
            goto err_register;
        }

        /* 申请成功 */
        (void)memset_s(ptr_clk_lookup, sizeof(struct clk_lookup), 0, sizeof(struct clk_lookup));

        ptr_clk_lookup->dev_id = NULL;
        ptr_clk_lookup->con_id = pmic_alloc_copy(pclk->name);
        ptr_clk_lookup->clk = pclk;

        drv_clkdev_add(ptr_clk_lookup);

        continue;

    err_register:
        osl_free((void*)init);
    err_init:
        osl_free((void*)clk_pmic);
    err_pmic_clk:
        return ;
    }

    pmu_print_error("pmic_clk setup ok\n");
    /* coverity[leaked_storage] */
    return ;
}


void  pmic_clk_init(void)
{
    struct device_node *node = NULL;

    /* 节点 */
    node = of_find_compatible_node(NULL, NULL, "hisilicon,pmic_clk_mdm");
    if (!node)
    {
        pmu_print_error("find pmic_clk_mdm err\n");
        return ;
    }

    pmic_clk_setup(node);
}


