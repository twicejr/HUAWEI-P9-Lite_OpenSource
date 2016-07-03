
#ifdef __cplusplus
		extern "C" {
#endif

#include <osl_bio.h>
#include "securec.h"
#include <osl_common.h>
#include <string.h>
#include <stdio.h>

#include <bsp_sysctrl.h>
#include <of.h>
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"
#include "bsp_dump.h"
#include "bsp_hardtimer.h"
#include <bsp_version.h>

#include "pdlock_balong.h"

struct pdlock_sysctrl g_sysctrl[sysctrl_sum] = {{{0},0,0}};
struct pdlock_state g_pdlock_state = {0,0};
struct pdlock_dump_record *g_pdlock_dump_record = NULL;
u32 *g_pdlock_dump_head = NULL;



static inline void hi_pdlock_get_reg(unsigned int *value,unsigned int base_address, u32 *pstreg)
 {
	 unsigned int mask = 0;
	 unsigned int temp = 0;
	 unsigned int reg  = base_address + pstreg[0];

	 temp	= readl(reg);
	 mask	= ((1U << (pstreg[2] - pstreg[1] + 1)) -1) << pstreg[1];
	 *value = temp & mask;
	 *value = (*value) >> pstreg[1];
 }



static inline void hi_pdlock_set_reg(unsigned int value, unsigned int base_address, u32 *pstreg)
{
	unsigned int reg	= base_address + pstreg[0];
	unsigned int temp	= 0;
	unsigned int mask	= 0;

	temp   = readl(reg);
	mask   = ((1U << (pstreg[2] - pstreg[1] + 1)) -1) << pstreg[1];
	value  = (temp & (~mask)) | ((value <<pstreg[1]) & mask);
	writel(value  ,reg);
}


s32 pdlock_reg_enable(struct device_node *child, u32 vir_enable_addr, u32 *enable_reg, u32 reg_sum)
{
	u32 i = 0, u = 0;
	const __be32 *p = NULL;
	struct property *prop = NULL;

	of_property_for_each_u32(child, "pdlock_enable_reg", prop, p, u)
	{
		enable_reg[i] = u;
		i++;
	}
	if(i != 3*reg_sum)
	{
		pdlock_print("Read pdlock_enable_reg failed!\n");
		return pdlock_error;
	}

	if(vir_enable_addr)
	{
		hi_pdlock_set_reg(1, vir_enable_addr, enable_reg);
		for(i = 3; i < 3*reg_sum; i=i+3)
		{
			hi_pdlock_set_reg(0, vir_enable_addr, (enable_reg + i));
		}
	}
	return pdlock_ok;
}


s32 pdlock_get_state_reg(struct device_node *child, u32 id, u32 state_reg_sum, u32 sysctrl_type)
{
	u32 i = 0, j = 0, u = 0;
	u32 mst_id = 0, operation = 0;
	s32 ret = 0;
	const __be32 *p = NULL;
	struct property *prop = NULL;
	const char *temp = NULL;

	of_property_for_each_u32(child, "pdlock_state_reg", prop, p, u)
	{
		if(i % 3 == 0)
		{
			g_sysctrl[sysctrl_type].bus[id].cfg[j].mst_reg_addr[0] = u;
		}
		else if(i % 3 == 1)
		{
			g_sysctrl[sysctrl_type].bus[id].cfg[j].mst_reg_addr[1] = u;
		}
		else
		{
			g_sysctrl[sysctrl_type].bus[id].cfg[j].mst_reg_addr[2] = u;
			j++;
		}
		i++;
	}
	if(i != 3*state_reg_sum || j != state_reg_sum)
	{
		pdlock_print("Read pdlock_state_reg failed!\n");
		return pdlock_error;
	}

	for(i = 0; i < state_reg_sum; i++)
	{
		ret = of_property_read_string_index(child, "pdlock_mst_name", (s32)i, &temp);
		ret |= of_property_read_u32_index(child, "pdlock_address_reg", i, &g_sysctrl[sysctrl_type].bus[id].cfg[i].error_address_offset);
		ret |= of_property_read_u32_index(child, "pdlock_dump_mst_id", i, &mst_id);
		ret |= of_property_read_u32_index(child, "pdlock_dump_operation", i, &operation);
		if(ret)
		{
			pdlock_print("Read pdlock_mst_name or pdlock_address_reg failed!\n");
			return pdlock_error;
		}
		(void)strcpy_s(g_sysctrl[sysctrl_type].bus[id].cfg[i].mst_name, 32, temp);
		g_sysctrl[sysctrl_type].bus[id].cfg[i].dump_mst_id = (u8)mst_id;
		g_sysctrl[sysctrl_type].bus[id].cfg[i].dump_operation = (u8)operation;
	}
	return pdlock_ok;
}


void pdlock_sysctrl_free(u32 sysctrl_type, u32 *enable_reg, u32 bus_sum)
{
	u32 i;

	if(NULL != enable_reg)
		pdlock_free(enable_reg);
	for(i = 0; i < bus_sum; i++)
	{
		if(NULL != g_sysctrl[sysctrl_type].bus[i].cfg)
			pdlock_free(g_sysctrl[sysctrl_type].bus[i].cfg);
	}
	if(NULL != g_sysctrl[sysctrl_type].bus)
		pdlock_free(g_sysctrl[sysctrl_type].bus);
}


void pdlock_sysctrl_init_free(u32 sysctrl_type)
{
	u32 i;

	for(i = 0; i < g_sysctrl[sysctrl_type].bus_sum; i++)
	{
		if(NULL != g_sysctrl[sysctrl_type].bus[i].cfg)
			pdlock_free(g_sysctrl[sysctrl_type].bus[i].cfg);
	}
	if(NULL != g_sysctrl[sysctrl_type].bus)
		pdlock_free(g_sysctrl[sysctrl_type].bus);
}

/*lint -save -e801*/

s32 pdlock_sysctrl_pd_setup(void)
{
	struct device_node *dev = NULL,*child = NULL;
	u32 reg_addr[4] = {0,0,0,0};
	s32 ret = 0;
	u32 bus_sum = 0, reg_sum = 0, id = 0, state_reg_sum = 0;
	u32 dump_bus_id = 0;
	u32 phy_enable_addr = 0, vir_enable_addr = 0;
	u32 *enable_reg = NULL;
	const char *node_name = "hisilicon,pdlock_pd_glb_balong";
	const char *temp = NULL;

	dev = of_find_compatible_node(NULL, NULL, node_name);
	if(NULL == dev)
	{
		pdlock_print("Read dev_node failed!\n");
		return pdlock_error;
	}

	ret = of_property_read_u32_array(dev, "pdlock_bus_sum", &bus_sum, 1);
	if(ret)
	{
		pdlock_print("Read pdlock_bus_sum failed!\n");
		return pdlock_error;
	}
	g_sysctrl[pd_glb].bus_sum = bus_sum;

	if(0 != bus_sum)
	{
		ret = of_property_read_u32_array(dev, "pdlock_reset_reg", reg_addr, 4);
		if(ret)
		{
			pdlock_print("Read pdlock_reset_reg failed!\n");
			return pdlock_error;
		}
		g_sysctrl[pd_glb].reset_reg_addr[base_addr] = (u32)bsp_sysctrl_addr_get((void *) reg_addr[0]);
		g_sysctrl[pd_glb].reset_reg_addr[addr_offset] = reg_addr[1];
		g_sysctrl[pd_glb].reset_reg_addr[start_bit] = reg_addr[2];
		g_sysctrl[pd_glb].reset_reg_addr[end_bit] = reg_addr[3];

		/*在初始化的时候，需要保证系统中不会遗留上一次未清掉的状态*/
        hi_pdlock_set_reg(1, g_sysctrl[pd_glb].reset_reg_addr[base_addr], (g_sysctrl[pd_glb].reset_reg_addr + 1));
		hi_pdlock_set_reg(0, g_sysctrl[pd_glb].reset_reg_addr[base_addr], (g_sysctrl[pd_glb].reset_reg_addr + 1));

		g_sysctrl[pd_glb].bus = (struct pdlock_bus *)pdlock_malloc(bus_sum*(sizeof(struct pdlock_bus)));
		if(!g_sysctrl[pd_glb].bus)
		{
			pdlock_print("Struct pdlock_bus bus malloc failed!\n");
			return pdlock_error;
		}

		memset_s(g_sysctrl[pd_glb].bus, bus_sum*(sizeof(struct pdlock_bus)), 0, bus_sum*(sizeof(struct pdlock_bus)));

		for_each_child_of_node(dev,child)
		{
			ret = of_property_read_u32_array(child, "pdlock_enable_reg_sum", &reg_sum, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_enable_reg_sum failed!\n");
				goto error_free;
			}

			enable_reg = (u32 *)pdlock_malloc(3*reg_sum*(sizeof(u32)));
			if(!enable_reg)
			{
				pdlock_print("Enable_reg malloc failed!\n");
				goto error_free;
			}
			memset_s(enable_reg, 3*reg_sum*(sizeof(u32)), 0, 3*reg_sum*(sizeof(u32)));

			ret = of_property_read_u32_array(child, "pdlock_base_address", &phy_enable_addr, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_base_address failed!\n");
				goto error_free;
			}

			vir_enable_addr = (u32)bsp_sysctrl_addr_get((void *)phy_enable_addr);

			ret = pdlock_reg_enable(child, vir_enable_addr, enable_reg, reg_sum);
			if(ret)
			{
				pdlock_print("pdlock_reg_enable failed!\n");
				goto error_free;
			}

			ret = of_property_read_u32_array(child, "pdlock_bus_id", &id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_id failed!\n");
				goto error_free;
			}

			g_sysctrl[pd_glb].bus[id].base_addr = vir_enable_addr;
			ret = of_property_read_string(child, "pdlock_bus_name", &temp);
			ret |= of_property_read_u32_array(child, "pdlock_state_reg_sum", &state_reg_sum, 1);
			ret |= of_property_read_u32_array(child, "pdlock_dump_bus_id", &dump_bus_id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_name or pdlock_state_reg_sum or pdlock_dump_bus_id failed!\n");
				goto error_free;
			}
			(void)strcpy_s(g_sysctrl[pd_glb].bus[id].busname, 16, temp);

			g_sysctrl[pd_glb].bus[id].dump_bus_id = (u8)dump_bus_id;
			g_sysctrl[pd_glb].bus[id].reg_state_sum = state_reg_sum;
			g_sysctrl[pd_glb].bus[id].cfg = (struct pdlock_cfg *)pdlock_malloc(state_reg_sum*(sizeof(struct pdlock_cfg)));
			if(!g_sysctrl[pd_glb].bus[id].cfg)
			{
				pdlock_print("struct pdlock_cfg cfg malloc failed!\n");
				goto error_free;
			}

			memset_s(g_sysctrl[pd_glb].bus[id].cfg, state_reg_sum*(sizeof(struct pdlock_cfg)), 0, state_reg_sum*(sizeof(struct pdlock_cfg)));

			ret = pdlock_get_state_reg(child, id, state_reg_sum, pd_glb);
			if(ret)
			{
				pdlock_print("pdlock_get_state_reg failed!\n");
				goto error_free;
			}

			pdlock_free(enable_reg);
		}
	}
	return pdlock_ok;

error_free:
	pdlock_sysctrl_free(pd_glb, enable_reg, bus_sum);
	return pdlock_error;
}


s32 pdlock_sysctrl_modem_setup(void)
{
	struct device_node *dev = NULL,*child = NULL;
	u32 reg_addr[4] = {0,0,0,0};
	s32 ret = 0;
	u32 bus_sum = 0, reg_sum = 0, id = 0, state_reg_sum = 0;
	u32 dump_bus_id = 0;
	u32 phy_enable_addr = 0, vir_enable_addr = 0;
	u32 *enable_reg = NULL;
	const char *node_name = "hisilicon,pdlock_modem_glb_balong";
	const char *temp = NULL;

	dev = of_find_compatible_node(NULL, NULL, node_name);
	if(NULL == dev)
	{
		pdlock_print("Read dev_node failed!\n");
		return pdlock_error;
	}

	ret = of_property_read_u32_array(dev, "pdlock_bus_sum", &bus_sum, 1);
	if(ret)
	{
		pdlock_print("Read pdlock_bus_sum failed!\n");
		return pdlock_error;
	}
	g_sysctrl[modem_glb].bus_sum = bus_sum;

	if(0 != bus_sum)
	{
		ret = of_property_read_u32_array(dev, "pdlock_reset_reg", reg_addr, 4);
		if(ret)
		{
			pdlock_print("Read pdlock_reset_reg failed!\n");
			return pdlock_error;
		}
		g_sysctrl[modem_glb].reset_reg_addr[base_addr] = (u32)bsp_sysctrl_addr_get((void *) reg_addr[0]);
		g_sysctrl[modem_glb].reset_reg_addr[addr_offset] = reg_addr[1];
		g_sysctrl[modem_glb].reset_reg_addr[start_bit] = reg_addr[2];
		g_sysctrl[modem_glb].reset_reg_addr[end_bit] = reg_addr[3];

        /*在初始化的时候，需要保证系统中不会遗留上一次未清掉的状态*/
        hi_pdlock_set_reg(1, g_sysctrl[modem_glb].reset_reg_addr[base_addr], (g_sysctrl[modem_glb].reset_reg_addr + 1));
		hi_pdlock_set_reg(0, g_sysctrl[modem_glb].reset_reg_addr[base_addr], (g_sysctrl[modem_glb].reset_reg_addr + 1));

		g_sysctrl[modem_glb].bus = (struct pdlock_bus *)pdlock_malloc(bus_sum*(sizeof(struct pdlock_bus)));
		if(!g_sysctrl[modem_glb].bus)
		{
			pdlock_print("Struct pdlock_bus bus malloc failed!\n");
			return pdlock_error;
		}
		memset_s(g_sysctrl[modem_glb].bus, bus_sum*(sizeof(struct pdlock_bus)), 0, bus_sum*(sizeof(struct pdlock_bus)));

		for_each_child_of_node(dev,child)
		{
			ret = of_property_read_u32_array(child, "pdlock_enable_reg_sum", &reg_sum, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_enable_reg_sum failed!\n");
				goto error_free;
			}

			enable_reg = (u32 *)pdlock_malloc(3*reg_sum*(sizeof(u32)));
			if(!enable_reg)
			{
				pdlock_print("Enable_reg malloc failed!\n");
				goto error_free;
			}
			memset_s(enable_reg, 3*reg_sum*(sizeof(u32)), 0, 3*reg_sum*(sizeof(u32)));

			ret = of_property_read_u32_array(child, "pdlock_base_address", &phy_enable_addr, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_base_address failed!\n");
				goto error_free;
			}
			vir_enable_addr = (u32)bsp_sysctrl_addr_get((void *)phy_enable_addr);

			ret = pdlock_reg_enable(child, vir_enable_addr, enable_reg, reg_sum);
			if(ret)
			{
				pdlock_print("pdlock_reg_enable failed!\n");
				goto error_free;
			}

			ret = of_property_read_u32_array(child, "pdlock_bus_id", &id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_id failed!\n");
				goto error_free;
			}
			g_sysctrl[modem_glb].bus[id].base_addr = vir_enable_addr;
			ret = of_property_read_string(child, "pdlock_bus_name", &temp);
			ret |= of_property_read_u32_array(child, "pdlock_state_reg_sum", &state_reg_sum, 1);
			ret |= of_property_read_u32_array(child, "pdlock_dump_bus_id", &dump_bus_id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_name or pdlock_state_reg_sum or pdlock_dump_bus_id failed!\n");
				goto error_free;
			}
			(void)strcpy_s(g_sysctrl[modem_glb].bus[id].busname, 16, temp);
			
			g_sysctrl[modem_glb].bus[id].reg_state_sum = state_reg_sum;
			g_sysctrl[modem_glb].bus[id].dump_bus_id = (u8)dump_bus_id;

			g_sysctrl[modem_glb].bus[id].cfg = (struct pdlock_cfg *)pdlock_malloc(state_reg_sum*(sizeof(struct pdlock_cfg)));
			if(!g_sysctrl[modem_glb].bus[id].cfg)
			{
				pdlock_print("struct pdlock_cfg cfg malloc failed!\n");
				goto error_free;
			}

			memset_s(g_sysctrl[modem_glb].bus[id].cfg, state_reg_sum*(sizeof(struct pdlock_cfg)), 0, state_reg_sum*(sizeof(struct pdlock_cfg)));

			ret = pdlock_get_state_reg(child, id, state_reg_sum, modem_glb);
			if(ret)
			{
				pdlock_print("pdlock_get_state_reg failed!\n");
				goto error_free;
			}

			pdlock_free(enable_reg);
		}
	}
	return pdlock_ok;

error_free:
	pdlock_sysctrl_free(modem_glb, enable_reg, bus_sum);
	return pdlock_error;
}


s32 pdlock_sysctrl_pcie_setup(void)
{
	struct device_node *dev = NULL,*child = NULL;
	u32 reg_addr[4];
	s32 ret = 0;
	u32 bus_sum = 0, reg_sum = 0, id = 0, state_reg_sum = 0;
	u32 dump_bus_id = 0;
	u32 vir_enable_addr = 0;
	u32 *enable_reg = NULL;
	const char *node_name = "hisilicon,pdlock_pcie_glb_balong";
	const char *temp = NULL;

	dev = of_find_compatible_node(NULL, NULL, node_name);
	if(NULL == dev)
	{
		pdlock_print("Read dev_node failed!\n");
		return pdlock_error;
	}

	ret = of_property_read_u32_array(dev, "pdlock_bus_sum", &bus_sum, 1);
	if(ret)
	{
		pdlock_print("Read pdlock_bus_sum failed!\n");
		return pdlock_error;
	}
	g_sysctrl[pcie_glb].bus_sum = bus_sum;

	if(0 != bus_sum)
	{
		ret = of_property_read_u32_array(dev, "pdlock_reset_reg", reg_addr, 4);
		if(ret)
		{
			pdlock_print("Read pdlock_reset_reg failed!\n");
			return pdlock_error;
		}

		/*sysctrl_pcie在C核没有进行映射*/
		//g_sysctrl[pcie_glb].reset_reg_addr[0] = (u32)bsp_sysctrl_addr_get((void *) reg_addr[0]);
		vir_enable_addr = (u32)of_iomap(dev, 0);
		g_sysctrl[pcie_glb].reset_reg_addr[base_addr] = vir_enable_addr;
		g_sysctrl[pcie_glb].reset_reg_addr[addr_offset] = reg_addr[1];
		g_sysctrl[pcie_glb].reset_reg_addr[start_bit] = reg_addr[2];
		g_sysctrl[pcie_glb].reset_reg_addr[end_bit] = reg_addr[3];

        /*在初始化的时候，需要保证系统中不会遗留上一次未清掉的状态*/
        hi_pdlock_set_reg(1, g_sysctrl[pcie_glb].reset_reg_addr[base_addr], (g_sysctrl[pcie_glb].reset_reg_addr + 1));
		hi_pdlock_set_reg(0, g_sysctrl[pcie_glb].reset_reg_addr[base_addr], (g_sysctrl[pcie_glb].reset_reg_addr + 1));

		g_sysctrl[pcie_glb].bus = (struct pdlock_bus *)pdlock_malloc(bus_sum*(sizeof(struct pdlock_bus)));
		if(!g_sysctrl[pcie_glb].bus)
		{
			pdlock_print("Struct pdlock_bus bus malloc failed!\n");
			return pdlock_error;
		}
		memset_s(g_sysctrl[pcie_glb].bus, bus_sum*(sizeof(struct pdlock_bus)), 0, bus_sum*(sizeof(struct pdlock_bus)));

		for_each_child_of_node(dev,child)
		{
			ret = of_property_read_u32_array(child, "pdlock_enable_reg_sum", &reg_sum, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_enable_reg_sum failed!\n");
				goto error_free;
			}

			enable_reg = (u32 *)pdlock_malloc(3*reg_sum*(sizeof(u32)));
			if(!enable_reg)
			{
				pdlock_print("Enable_reg malloc failed!\n");
				goto error_free;
			}

			memset_s(enable_reg, 3*reg_sum*(sizeof(u32)), 0, 3*reg_sum*(sizeof(u32)));

			#if 0
			ret = of_property_read_u32_array(child, "pdlock_base_address", &phy_enable_addr, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_base_address failed!\n");
				goto error_free;
			}
			vir_enable_addr = (u32)bsp_sysctrl_addr_get((void *)phy_enable_addr);
			#endif

			ret = pdlock_reg_enable(child, vir_enable_addr, enable_reg, reg_sum);
			if(ret)
			{
				pdlock_print("pdlock_reg_enable failed!\n");
				goto error_free;
			}


			ret = of_property_read_u32_array(child, "pdlock_bus_id", &id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_id failed!\n");
				goto error_free;
			}
			g_sysctrl[pcie_glb].bus[id].base_addr = vir_enable_addr;

			ret = of_property_read_string(child, "pdlock_bus_name", &temp);
			ret |= of_property_read_u32_array(child, "pdlock_state_reg_sum", &state_reg_sum, 1);
			ret |= of_property_read_u32_array(child, "pdlock_dump_bus_id", &dump_bus_id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_name or pdlock_state_reg_sum or pdlock_dump_bus_id failed!\n");
				goto error_free;
			}
			(void)strcpy_s(g_sysctrl[pcie_glb].bus[id].busname, 16, temp);
			
			g_sysctrl[pcie_glb].bus[id].reg_state_sum = state_reg_sum;
			g_sysctrl[pcie_glb].bus[id].dump_bus_id = (u8)dump_bus_id;

			g_sysctrl[pcie_glb].bus[id].cfg = (struct pdlock_cfg *)pdlock_malloc(state_reg_sum*(sizeof(struct pdlock_cfg)));
			if(!g_sysctrl[pcie_glb].bus[id].cfg)
			{
				pdlock_print("struct pdlock_cfg cfg malloc failed!\n");
				goto error_free;
			}

			memset_s(g_sysctrl[pcie_glb].bus[id].cfg, state_reg_sum*(sizeof(struct pdlock_cfg)), 0, state_reg_sum*(sizeof(struct pdlock_cfg)));

			ret = pdlock_get_state_reg(child, id, state_reg_sum, pcie_glb);
			if(ret)
			{
				pdlock_print("pdlock_get_state_reg failed!\n");
				goto error_free;
			}

			pdlock_free(enable_reg);
		}
	}
	return pdlock_ok;

error_free:
	pdlock_sysctrl_free(pcie_glb, enable_reg, bus_sum);
	return pdlock_error;
}


s32 pdlock_sysctrl_ao_setup(void)
{
	struct device_node *dev = NULL,*child = NULL;
	u32 reg_addr[4];
	s32 ret = 0;
	u32 bus_sum = 0, reg_sum = 0, id = 0, state_reg_sum = 0;
	u32 dump_bus_id = 0;
	u32 phy_enable_addr = 0, vir_enable_addr = 0;
	u32 *enable_reg = NULL;
	const char *node_name = "hisilicon,pdlock_ao_glb_balong";
	const char *temp = NULL;

	dev = of_find_compatible_node(NULL, NULL, node_name);
	if(NULL == dev)
	{
		pdlock_print("Read dev_node failed!\n");
		return pdlock_error;
	}

	ret = of_property_read_u32_array(dev, "pdlock_bus_sum", &bus_sum, 1);
	if(ret)
	{
		pdlock_print("Read pdlock_bus_sum failed!\n");
		return pdlock_error;
	}
	g_sysctrl[ao_glb].bus_sum = bus_sum;

	if(0 != bus_sum)
	{
		ret = of_property_read_u32_array(dev, "pdlock_reset_reg", reg_addr, 4);
		if(ret)
		{
			pdlock_print("Read pdlock_reset_reg failed!\n");
			return pdlock_error;
		}
		g_sysctrl[ao_glb].reset_reg_addr[base_addr] = (u32)bsp_sysctrl_addr_get((void *) reg_addr[0]);
		g_sysctrl[ao_glb].reset_reg_addr[addr_offset] = reg_addr[1];
		g_sysctrl[ao_glb].reset_reg_addr[start_bit] = reg_addr[2];
		g_sysctrl[ao_glb].reset_reg_addr[end_bit] = reg_addr[3];

        /*在初始化的时候，需要保证系统中不会遗留上一次未清掉的状态*/
        hi_pdlock_set_reg(1, g_sysctrl[ao_glb].reset_reg_addr[base_addr], (g_sysctrl[ao_glb].reset_reg_addr + 1));
		hi_pdlock_set_reg(0, g_sysctrl[ao_glb].reset_reg_addr[base_addr], (g_sysctrl[ao_glb].reset_reg_addr + 1));

		g_sysctrl[ao_glb].bus = (struct pdlock_bus *)pdlock_malloc(bus_sum*(sizeof(struct pdlock_bus)));
		if(!g_sysctrl[ao_glb].bus)
		{
			pdlock_print("Struct pdlock_bus bus malloc failed!\n");
			return pdlock_error;
		}
		memset_s(g_sysctrl[ao_glb].bus, bus_sum*(sizeof(struct pdlock_bus)), 0, bus_sum*(sizeof(struct pdlock_bus)));

		for_each_child_of_node(dev,child)
		{
			ret = of_property_read_u32_array(child, "pdlock_enable_reg_sum", &reg_sum, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_enable_reg_sum failed!\n");
				goto error_free;
			}

			enable_reg = (u32 *)pdlock_malloc(3*reg_sum*(sizeof(u32)));
			if(!enable_reg)
			{
				pdlock_print("Enable_reg malloc failed!\n");
				goto error_free;
			}

			memset_s(enable_reg, 3*reg_sum*(sizeof(u32)), 0, 3*reg_sum*(sizeof(u32)));

			ret = of_property_read_u32_array(child, "pdlock_base_address", &phy_enable_addr, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_base_address failed!\n");
				goto error_free;
			}
			vir_enable_addr = (u32)bsp_sysctrl_addr_get((void *)phy_enable_addr);

			ret = pdlock_reg_enable(child, vir_enable_addr, enable_reg, reg_sum);
			if(ret)
			{
				pdlock_print("pdlock_reg_enable failed!\n");
				goto error_free;
			}

			ret = of_property_read_u32_array(child, "pdlock_bus_id", &id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_id failed!\n");
				goto error_free;
			}
			g_sysctrl[ao_glb].bus[id].base_addr = vir_enable_addr;
			ret = of_property_read_string(child, "pdlock_bus_name", &temp);
			ret |= of_property_read_u32_array(child, "pdlock_state_reg_sum", &state_reg_sum, 1);
			ret |= of_property_read_u32_array(child, "pdlock_dump_bus_id", &dump_bus_id, 1);
			if(ret)
			{
				pdlock_print("Read pdlock_bus_name or pdlock_state_reg_sum or pdlock_dump_bus_id failed!\n");
				goto error_free;
			}
			(void)strcpy_s(g_sysctrl[ao_glb].bus[id].busname, 16, temp);
			
			g_sysctrl[ao_glb].bus[id].reg_state_sum = state_reg_sum;
			g_sysctrl[ao_glb].bus[id].dump_bus_id = (u8)dump_bus_id;

			g_sysctrl[ao_glb].bus[id].cfg = (struct pdlock_cfg *)pdlock_malloc(state_reg_sum*(sizeof(struct pdlock_cfg)));
			if(!g_sysctrl[ao_glb].bus[id].cfg)
			{
				pdlock_print("struct pdlock_cfg cfg malloc failed!\n");
				goto error_free;
			}

			memset_s(g_sysctrl[ao_glb].bus[id].cfg, state_reg_sum*(sizeof(struct pdlock_cfg)), 0, state_reg_sum*(sizeof(struct pdlock_cfg)));

			ret = pdlock_get_state_reg(child, id, state_reg_sum, ao_glb);
			if(ret)
			{
				pdlock_print("pdlock_get_state_reg failed!\n");
				goto error_free;
			}

			pdlock_free(enable_reg);
		}
	}
	return pdlock_ok;

error_free:
	pdlock_sysctrl_free(ao_glb, enable_reg, bus_sum);
	return pdlock_error;
}
/*lint -restore*/


static irqreturn_t pdlock_int_handler(void *arg)
{
	u32 i, j, k;
	u32 temp1 = 0, temp2 = 0, temp3 = 0, flag = 0;
	for(i = 0; i < sysctrl_sum; i++)
	{
		for(j = 0; j < g_sysctrl[i].bus_sum; j++)
		{
			for(k = 0; k < g_sysctrl[i].bus[j].reg_state_sum; k++)
			{
				hi_pdlock_get_reg(&temp1, g_sysctrl[i].bus[j].base_addr, g_sysctrl[i].bus[j].cfg[k].mst_reg_addr);
				if(temp1 != 0)
				{
					temp2 = readl(g_sysctrl[i].bus[j].base_addr + g_sysctrl[i].bus[j].cfg[k].error_address_offset);
					pdlock_print("**************Pdlock info**************\n");
					pdlock_print("ERRO_BUS_NAME:%s\n",g_sysctrl[i].bus[j].busname);
					pdlock_print("MST_NAME AND OPERATION_TYPE:%s\n",g_sysctrl[i].bus[j].cfg[k].mst_name);
					pdlock_print("SLAVE_ADDRESS:0x%x\n",temp2);
					pdlock_print("GLB_APB\\MDM_APB\\M3_APB SLAVE_ADDRESS HIGH 20 BITS AVAILABLE\n");
					pdlock_print("----------------------------------------\n");
					flag = 1;
					if(NULL != g_pdlock_dump_record)
					{
						if((g_pdlock_dump_head[total]) < FIRST_RECORD)
						{
							temp3 = g_pdlock_dump_head[total];
							g_pdlock_dump_record[temp3].bus_id = g_sysctrl[i].bus[j].dump_bus_id;
							g_pdlock_dump_record[temp3].mst_id = g_sysctrl[i].bus[j].cfg[k].dump_mst_id;
							g_pdlock_dump_record[temp3].operation = g_sysctrl[i].bus[j].cfg[k].dump_operation;
							g_pdlock_dump_record[temp3].slave_addr = temp2;
							g_pdlock_dump_record[temp3].slice = bsp_get_slice_value();
							g_pdlock_dump_head[offset]++;
							g_pdlock_dump_head[total]++;
						}
						else
						{
							temp3 = ((g_pdlock_dump_head[total] - FIRST_RECORD) % (MAX_RECORD - FIRST_RECORD)) + FIRST_RECORD;
							g_pdlock_dump_record[temp3].bus_id = g_sysctrl[i].bus[j].dump_bus_id;
							g_pdlock_dump_record[temp3].mst_id = g_sysctrl[i].bus[j].cfg[k].dump_mst_id;
							g_pdlock_dump_record[temp3].operation = g_sysctrl[i].bus[j].cfg[k].dump_operation;
							g_pdlock_dump_record[temp3].slave_addr = temp2;
							g_pdlock_dump_record[temp3].slice = bsp_get_slice_value();
							g_pdlock_dump_head[offset] = temp3 + 1;
							g_pdlock_dump_head[total]++;
						}
					}
				}
			}
		}
		if(flag)
		{
			hi_pdlock_set_reg(1, g_sysctrl[i].reset_reg_addr[base_addr], (g_sysctrl[i].reset_reg_addr + 1));
			hi_pdlock_set_reg(0, g_sysctrl[i].reset_reg_addr[base_addr], (g_sysctrl[i].reset_reg_addr + 1));
			flag = 0;
		}
	}

	if(g_pdlock_state.reset_enable == PDLOCK_RESET_ENABLE)
	{
		system_error(DRV_ERRNO_PDLOCK, 0, 0, NULL, 0);
	}
	return IRQ_HANDLED;
}


u32 pdlock_dump_handler(void)
{
	u32 i, j, k;
	u32 temp1 = 0, temp2 = 0, temp3 = 0, len = 0;
	char data[100] = {0};
	for(i = 0; i < sysctrl_sum; i++)
		for(j = 0; j < g_sysctrl[i].bus_sum; j++)
			for(k = 0; k < g_sysctrl[i].bus[j].reg_state_sum; k++)
			{
				hi_pdlock_get_reg(&temp1, g_sysctrl[i].bus[j].base_addr, g_sysctrl[i].bus[j].cfg[k].mst_reg_addr);
				if(temp1 != 0)
				{
					temp2 = readl(g_sysctrl[i].bus[j].base_addr + g_sysctrl[i].bus[j].cfg[k].error_address_offset);
					len = (u32)sprintf_s(data, 100, "********Pdlock info begin********\n");
					(void)dmesg_write(data, len);
					len = (u32)sprintf_s(data, 100, "ERRO_BUS_NAME:%s\n",g_sysctrl[i].bus[j].busname);
					(void)dmesg_write(data, len);
					len = (u32)sprintf_s(data, 100, "MST_NAME AND OPERATION_TYPE:%s\n",g_sysctrl[i].bus[j].cfg[k].mst_name);
					(void)dmesg_write(data, len);
					len = (u32)sprintf_s(data, 100, "SLAVE_ADDRESS:0x%x\n",temp2);
					(void)dmesg_write(data, len);
					len = (u32)sprintf_s(data, 100, "GLB_APB\\MDM_APB\\M3_APB SLAVE_ADDRESS HIGH 20 BITS AVAILABLE\n");
					(void)dmesg_write(data, len);
					len = (u32)sprintf_s(data, 100, "----------------------------------------\n");
					(void)dmesg_write(data, len);

					if(NULL != g_pdlock_dump_record)
					{
						if((g_pdlock_dump_head[total]) < FIRST_RECORD)
						{
							temp3 = g_pdlock_dump_head[total];
							g_pdlock_dump_record[temp3].bus_id = g_sysctrl[i].bus[j].dump_bus_id;
							g_pdlock_dump_record[temp3].mst_id = g_sysctrl[i].bus[j].cfg[k].dump_mst_id;
							g_pdlock_dump_record[temp3].operation = g_sysctrl[i].bus[j].cfg[k].dump_operation;
							g_pdlock_dump_record[temp3].slave_addr = temp2;
							g_pdlock_dump_record[temp3].slice = bsp_get_slice_value();
							g_pdlock_dump_head[offset]++;
							g_pdlock_dump_head[total]++;
						}
						else
						{
							temp3 = ((g_pdlock_dump_head[total] - FIRST_RECORD) % (MAX_RECORD - FIRST_RECORD)) + FIRST_RECORD;
							g_pdlock_dump_record[temp3].bus_id = g_sysctrl[i].bus[j].dump_bus_id;
							g_pdlock_dump_record[temp3].mst_id = g_sysctrl[i].bus[j].cfg[k].dump_mst_id;
							g_pdlock_dump_record[temp3].operation = g_sysctrl[i].bus[j].cfg[k].dump_operation;
							g_pdlock_dump_record[temp3].slave_addr = temp2;
							g_pdlock_dump_record[temp3].slice = bsp_get_slice_value();
							g_pdlock_dump_head[offset] = temp3 + 1;
							g_pdlock_dump_head[total]++;
						}
					}
				}
			}
	return pdlock_ok;
}


s32 bsp_pdlock_init(void)
{
	struct device_node *dev = NULL;
	s32 ret = 0;
	u32 irq = 0;
	u8 *dump_base = NULL;
	const char *node_name = "hisilicon,pdlock_irq_balong";
	DRV_PDLOCK_CFG_STRU cfg;
	
	if(BSP_OK != bsp_nvm_read(NV_ID_DRV_PDLOCK, (u8 *)&cfg, sizeof(DRV_PDLOCK_CFG_STRU)))
	{
		pdlock_print("Pdlock read nv 0x%x error\n", NV_ID_DRV_PDLOCK);
		return pdlock_error;
	}
	else
	{
		if(cfg.enable == PDLOCK_ENABLE)
		{
			g_pdlock_state.enable = cfg.enable;
			g_pdlock_state.reset_enable = cfg.reset_enable;

			ret  = pdlock_sysctrl_pd_setup();
			if(ret)
			{
				pdlock_print("Pdlock_sysctrl_pd setup failed!\n");
				return pdlock_error;
			}

			ret = pdlock_sysctrl_modem_setup();
			if(ret)
			{
				pdlock_print("Pdlock_sysctrl_modem setup failed!\n");
				pdlock_sysctrl_init_free(pd_glb);
				return pdlock_error;
			}

			ret = pdlock_sysctrl_pcie_setup();
			if(ret)
			{
				pdlock_print("Pdlock_sysctrl_pcie setup failed!\n");
				pdlock_sysctrl_init_free(pd_glb);
				pdlock_sysctrl_init_free(modem_glb);
				return pdlock_error;
			}

			ret = pdlock_sysctrl_ao_setup();
			if(ret)
			{
				pdlock_print("Pdlock_sysctrl_ao setup failed!\n");
				pdlock_sysctrl_init_free(pd_glb);
				pdlock_sysctrl_init_free(modem_glb);
				pdlock_sysctrl_init_free(pcie_glb);
				return pdlock_error;
			}

			/*申请4*sizeof(u32) + MAX_RECORD*sizeof(struct pdlock_dump_record)空间，其中4*sizeof(u32)代表dump的头信息*/
			dump_base = bsp_dump_register_field(PDLOCK_DUMP_SAVE_MOD, "pdlock", 0, 0, 4*sizeof(u32) + MAX_RECORD*sizeof(struct pdlock_dump_record), 0);
			if(NULL == dump_base)
			{
				pdlock_print("Pdlock get dump space failed!\n");
			}
			else
			{
				memset_s(dump_base, 4*sizeof(u32) + MAX_RECORD*sizeof(struct pdlock_dump_record), 0, 4*sizeof(u32) + MAX_RECORD*sizeof(struct pdlock_dump_record));
				g_pdlock_dump_head = (u32 *)dump_base;
				g_pdlock_dump_head[magic] = 0x5a5a5a5a;
				g_pdlock_dump_head[max_log] = MAX_RECORD;
				g_pdlock_dump_head[total] = 0;
				g_pdlock_dump_head[offset] = 0;
				g_pdlock_dump_record = (struct pdlock_dump_record *)(g_pdlock_dump_head + 4);
			}

			dev = of_find_compatible_node(NULL, NULL, node_name);
			if(NULL == dev)
			{
				pdlock_print("dev_node not found!\n");
				pdlock_sysctrl_init_free(pd_glb);
				pdlock_sysctrl_init_free(modem_glb);
				pdlock_sysctrl_init_free(pcie_glb);
				pdlock_sysctrl_init_free(ao_glb);
				return pdlock_error;
			}
			irq = irq_of_parse_and_map(dev, 0);
			ret = request_irq(irq, (irq_handler_t)pdlock_int_handler, 0, "Pdlock irq", NULL);
			if(ret)
			{
				pdlock_print("Pdlock_int_handler request irq failed.\n");
				pdlock_sysctrl_init_free(pd_glb);
				pdlock_sysctrl_init_free(modem_glb);
				pdlock_sysctrl_init_free(pcie_glb);
				pdlock_sysctrl_init_free(ao_glb);
				return pdlock_error;
			}

			if(BSP_ERROR == bsp_dump_register_hook("PDLOCK_CCORE", (dump_hook)pdlock_dump_handler))
			{
				pdlock_print("Pdlock dump register fail\n");
				pdlock_sysctrl_init_free(pd_glb);
				pdlock_sysctrl_init_free(modem_glb);
				pdlock_sysctrl_init_free(pcie_glb);
				pdlock_sysctrl_init_free(ao_glb);
				return BSP_ERROR;
			}
			 
			pdlock_print("pdlock init ok\n");
		}
	}
	return pdlock_ok;
}


#ifdef __cplusplus
}
#endif

