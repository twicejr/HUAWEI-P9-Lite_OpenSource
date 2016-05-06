/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  hi_bbp.c
*
*   作    者 :  x00195528
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
#include <string.h>
#include <securec.h>
#include <osl_malloc.h>
#include <osl_err.h>
#include <osl_spinlock.h>
#include <of.h>
#include <bsp_version.h>
#include "pmu_pmic.h"
#include "pmu_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  NAME_LENTH                    32

extern struct pmic_volt_info g_pmic_voltinfo;
extern struct pmic_xo_info g_pmic_xoinfo;
extern struct dcdc_info g_pmu_exdcdc;

typedef void (*of_pmu_init_cb_t)(struct device_node *);

void  pmic_volt_common_setup(struct device_node *dev_node , u32 id)
{
    struct pmic_volt_ctrl *volt_ctrl;
    u32 reg_size = sizeof(struct pmic_volt_reg)/sizeof(u32);/*dts 每个寄存器子节点的大小*/

    volt_ctrl = (struct pmic_volt_ctrl *)&(g_pmic_voltinfo.volt_ctrl[id]);

    (void)of_property_read_string_index(dev_node,"volt_name",0,&volt_ctrl->name);
    (void)of_property_read_u32_array(dev_node, "reg_ctrl",(u32*)&(volt_ctrl->volt_reg),reg_size);
    (void)of_property_read_u32_index(dev_node, "off_on_delay",0,&volt_ctrl->off_on_delay);

    spin_lock_init(&g_pmic_voltinfo.volt_ctrl[id].volt_lock);
}
void  pmic_volt_table_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;
    struct device_node *child_node = NULL;
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    u32 id = 0;
    u32 table_size = 0;

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node,"volt_id",0,&id);
        if (ret) {
            pmu_print_error("get volt_id info from dts failed!\n");
            return;
        };
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[id];
        volt_ctrl->id = id;
        volt_ctrl->voltage_flag = VOLT_TABLE;

        pmic_volt_common_setup(child_node,id);
        (void)of_property_read_u32_index(child_node, "voltage_nums",0,(u32*)&(volt_ctrl->voltage_nums));
        table_size = sizeof(u32)*(volt_ctrl->voltage_nums);
        volt_ctrl->voltage_table = osl_malloc(table_size);
        if(IS_ERR(volt_ctrl->voltage_table))
        {
            pmu_print_error("volt_id %d malloc voltage table failed!\n",id);
            return;
        }
        (void)memset_s((void *)volt_ctrl->voltage_table,table_size,0,table_size);

        ret = of_property_read_u32_array(child_node, "voltage_table",
                        (u32 *)(volt_ctrl->voltage_table), volt_ctrl->voltage_nums);
        if (ret) {
            pmu_print_error("volt_id %d get table info from dts failed,errid %d!\n",id,ret);
            free((void*)(volt_ctrl->voltage_table));
            return;
        };
    };
}
void  pmic_volt_linear_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;
    struct device_node *child_node = NULL;
    struct pmic_volt_ctrl *volt_ctrl;
    u32 id = 0;

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node,"volt_id",0,&id);
        if (ret) {
            pmu_print_error("get volt_id info from dts failed!\n");
            return;
        };
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[id];
        volt_ctrl->id = id;
        volt_ctrl->voltage_flag = VOLT_LINEAR;

        pmic_volt_common_setup(child_node,id);
        ret = of_property_read_u32_index(child_node, "voltage_nums",0,(u32*)&(volt_ctrl->voltage_nums));
        ret |= of_property_read_u32_index(child_node, "voltage_base_step",0,&(volt_ctrl->voltage_base));
        ret |= of_property_read_u32_index(child_node, "voltage_base_step",1,&(volt_ctrl->voltage_step));

        if (ret) {
            pmu_print_error("get linear info from dts failed!\n");
            return;
        };
    };
}
void  pmic_volt_const_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;
    struct device_node *child_node = NULL;
    struct pmic_volt_ctrl *volt_ctrl;
    u32 id = 0;

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node,"volt_id",0,&id);
        if (ret) {
            pmu_print_error("get volt_id info from dts failed\n");
            return;
        };
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[id];
        volt_ctrl->id = id;
        volt_ctrl->voltage_flag = VOLT_CONST;

        pmic_volt_common_setup(child_node,id);
        ret = of_property_read_u32_index(child_node, "voltage_nums",0,(u32*)&(volt_ctrl->voltage_nums));
        ret |= of_property_read_u32_index(child_node, "voltage_const",0,&(volt_ctrl->voltage_const));

        if (ret) {
            pmu_print_error("get const info from dts failed\n");
            return;
        };
    };
}

static const struct of_device_id g_pmic_of_device_init[] =
{
        { .compatible = "hisilicon,pmic_volt_table",    .data = pmic_volt_table_setup, },
        { .compatible = "hisilicon,pmic_volt_linear", .data = pmic_volt_linear_setup, },
        { .compatible = "hisilicon,pmic_volt_const",     .data = pmic_volt_const_setup, },
        {},
};
void  of_pmu_init(const struct of_device_id *matches)
{
    struct device_node *np;

    if (!matches)
    {
        return ;
    }

    for_each_matching_node(np, matches)
    {
        if (!(strcmp("pmic_lastnode", np->name)))
        {
            break;
        }

        const struct of_device_id *match = of_match_node(matches, np);
        of_pmu_init_cb_t pmu_init_cb = match->data;/*lint !e158*/
        pmu_init_cb(np);
    }

    return ;
}
void pmic_volt_dts_init(void)
{
    struct device_node *dev_node = NULL;
    int ret = BSP_OK;
    u32 volt_num = 0;
    u32 attr_size = 0;

    dev_node = of_find_compatible_node(NULL, NULL, "hisilicon,pmic_volt_mdm");
    if(NULL == dev_node)
    {
        pmu_print_error("pmic device node not found!\n");
        return;
    }
    /*读取电源总数*/
    ret = of_property_read_u32_index(dev_node,"pmic_volt_num",0,(u32*)&g_pmic_voltinfo.volt_min);
    ret |= of_property_read_u32_index(dev_node,"pmic_volt_num",1,(u32*)&g_pmic_voltinfo.volt_max);
    if(ret)
    {
        pmu_print_error("read pmic_volt_num from dts failed,err_id %d!\n",ret);
        return;
    }
    volt_num = (g_pmic_voltinfo.volt_max - g_pmic_voltinfo.volt_min + 1);
    attr_size = sizeof(struct pmic_volt_ctrl)*volt_num;
    g_pmic_voltinfo.volt_ctrl= (struct pmic_volt_ctrl *)osl_malloc(attr_size);
    if(IS_ERR(g_pmic_voltinfo.volt_ctrl))
    {
        pmu_print_error("pmic malloc voltage ctrl failed!\n");
        return;
    }
    (void)memset_s((void *)g_pmic_voltinfo.volt_ctrl,attr_size,0,attr_size);

    of_pmu_init(g_pmic_of_device_init);

}

void  pmic_xo_dts_init(void)
{
    struct device_node *dev_node = NULL;
    struct device_node *child_node = NULL;
    char node_name[NAME_LENTH]   = "hisilicon,pmic_xo";
    int ret = BSP_OK;
    u32 rf_id = 0;
    u32 regctrl_size = sizeof(struct xorf_reg_ctrl)/sizeof(u32);
    u32 freqctrl_size = sizeof(struct xorf_freq_ctrl)/sizeof(u32);
    u32 ctrl_size = 0;
    char* version = 0;

    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
    {

        version = pmic_version_get();

        /* 统一切新pmu之前，对老pmu的兼容 */
        if(!strncmp(version,"6421",strlen("6421")))
        {
            (void)snprintf_s(node_name,NAME_LENTH,NAME_LENTH,"hisilicon,pmic_xo_hi%s",version);
        }
    }
    dev_node = of_find_compatible_node(NULL, NULL, node_name);
    if(NULL == dev_node)
    {
        pmu_print_error("pmic_xorf device node not found!\n");
        return;
    }
    /*get c1c2 ctrl from dts*/
    ret = of_property_read_u32_array(dev_node, "c1c2_ctrl",(u32 *)&(g_pmic_xoinfo.xo_ctrl),sizeof(struct xo_reg_ctrl)/sizeof(u32));
    if(ret)
    {
        pmu_print_error("get c1c2_ctrl info from dts failed,errid %d\n",ret);
    }
    g_pmic_xoinfo.xorf_num = of_get_child_count(dev_node);
    ctrl_size = sizeof(struct pmic_xorf_ctrl)*(g_pmic_xoinfo.xorf_num);
    g_pmic_xoinfo.xorf_ctrl= (struct pmic_xorf_ctrl *)osl_malloc(ctrl_size);
    if(IS_ERR(g_pmic_xoinfo.xorf_ctrl))
    {
        pmu_print_error("malloc xorf_ctrl failed!\n");
        return;
    }
    (void)memset_s((void *)g_pmic_xoinfo.xorf_ctrl,ctrl_size,0,ctrl_size);

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node,"rf_id",0,&rf_id);
        if (ret) {
            pmu_print_error("get rf_id from dts failed,errid %d\n",ret);
            return;
        }
        g_pmic_xoinfo.xorf_ctrl[rf_id].rf_id = rf_id;
        
        ret = of_property_read_u32_array(child_node,"rf_clk",(u32 *)&(g_pmic_xoinfo.xorf_ctrl[rf_id].rf_clk),freqctrl_size);
        if (ret) {
            g_pmic_xoinfo.xorf_ctrl[rf_id].rf_clk.freq_value = INVALIED_VALUE;
        }
        
        ret = of_property_read_u32_array(child_node, "reg_ctrl",(u32 *)&(g_pmic_xoinfo.xorf_ctrl[rf_id].reg_ctrl),regctrl_size);
        ret |= of_property_read_u32_array(child_node, "freq_ctrl",(u32 *)&(g_pmic_xoinfo.xorf_ctrl[rf_id].freq_ctrl),freqctrl_size);
        if (ret) {
            pmu_print_error("rf_id %d get xorf info from dts failed,errid %d!\n",rf_id,ret);
            return;
        };
    };
}
void dcdc_dts_init(void)
{
    struct device_node *dev_node = NULL;
    struct device_node *child_node = NULL;
    u32 dc_id = 0;
    u32 ctrl_size = 0;
    int ret = 0;

    dev_node = of_find_compatible_node(NULL, NULL, "hisilicon,pmu_dcdc_mdm");
    if(NULL == dev_node)
    {
        pmu_print_error("pmu_dcdc device node not found\n");
        return;
    }
    /*获取dcdc总数*/
    g_pmu_exdcdc.dc_num= of_get_child_count(dev_node);
    ctrl_size = sizeof(struct dcdc_ctrl)*(g_pmu_exdcdc.dc_num);
    g_pmu_exdcdc.dc_ctrl= (struct dcdc_ctrl *)osl_malloc(ctrl_size);
    if(IS_ERR(g_pmu_exdcdc.dc_ctrl))
    {
        pmu_print_error("malloc dc_ctrl failed\n");
        return;
    }
    (void)memset_s((void *)g_pmu_exdcdc.dc_ctrl,ctrl_size,0,ctrl_size);

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "dc_id", 0,&dc_id);
        if(ret)
        {
            pmu_print_error("pmu_dcdc get dc_id for dts failed,err_id %d!\n",ret);
            return;
        }
        (void)of_property_read_string_index(child_node,"dc_name",0,&g_pmu_exdcdc.dc_ctrl[dc_id].name);
        ret = of_property_read_u32_index(child_node, "gpio_id", 0,&g_pmu_exdcdc.dc_ctrl[dc_id].gpio_id);
        if(ret)
        {
            pmu_print_error("pmu_dcdc get gpio_id for dts failed,err_id %d!\n",ret);
            return;
        }
    }

    pmu_print_error("init ok!\n");

}

#ifdef __cplusplus
}
#endif
