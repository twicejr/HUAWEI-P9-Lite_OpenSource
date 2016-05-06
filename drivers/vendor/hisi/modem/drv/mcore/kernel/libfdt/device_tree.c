/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  device_tree.c
*
*   作    者 :  y00184236
*
*   描    述 :  提供设备树操作驱动
*
*   修改记录 :  2014年07月28日  v1.00  y00184236  创建
*
*************************************************************************/
#include <product_config.h>
#include <osl_types.h>
#include <printk.h>
#include <libfdt.h>

struct device_node of_allnodes = {0};

struct device_node *of_find_compatible_node(struct device_node *from,const char *type,const char *compat)
{
	struct device_node *dev = &of_allnodes;
	long flags = 0;

	if (NULL == compat)
	{
		return NULL;
	}

	UNUSED(flags);
	spin_lock_irqsave(&(dev->lock), flags);
	dev->offset = fdt_node_offset_by_compatible((const void *)DDR_MCORE_DTS_ADDR, -1, compat);
	spin_unlock_irqrestore(&(dev->lock), flags);
	if (dev->offset < 0) 
	{
		printk("no %s compatible\n", compat);
		return NULL;
	}

	return dev;
}

void *of_iomap(struct device_node *np, int index)
{
	u32 *reg = NULL;
	int len = 0;
	int cells_size = 2;

	/* step2-1: get node value, reg cell has 1 cell, which has 2 items */
	reg = (u32 *)fdt_getprop((const void *)DDR_MCORE_DTS_ADDR, np->offset, "reg", &len);
	if((index * cells_size * sizeof(len)) > len)
	{
		printk("of_iomap index err\n");
		/* coverity[NULL_RETURNS] */
		return NULL;
	}

	return (void *)cpu_to_fdt32(*(reg + index * cells_size));
}
unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
	u32 *reg = NULL;
	int len = 0;
	int cells_size = 3;

	/* step2-2: get node value, interrupts cell has 2 cells, which has 3 items */
	reg = (u32 *)fdt_getprop((const void *)DDR_MCORE_DTS_ADDR, dev->offset, "interrupts", &len);
	if((index * cells_size* sizeof(len)) > len)
	{
		printk("irq_of_parse_and_map index err\n");
		return 0;
	}
	return (unsigned int)cpu_to_fdt32(*(reg + 1 + index * cells_size));
}

unsigned int of_property_read_u32_array(struct device_node *dev, const char *propname, unsigned int *out_values, unsigned int sz)
{
	u32 *reg = NULL;
	int len = 0;

	/*  get node value, cell has 1 cells, which has 3 items */
	reg = (u32 *)fdt_getprop((const void *)DDR_MCORE_DTS_ADDR, dev->offset, propname, &len);
	if(reg == NULL)
	{
		printk("no %s property\n", propname);
		return 1;
	}

	while (sz--)
		*out_values++ = (unsigned int)cpu_to_fdt32(*reg++);
	return 0;
}

int of_property_read_string(struct device_node *np, const char *propname, const char **out_string)
{
	void *prop = NULL;
	prop = (void*)fdt_getprop((const void *)DDR_MCORE_DTS_ADDR, np->offset, propname, NULL);
	if (prop == NULL)
	{
		printk("no %s property\n", propname);
		return 1;
	}

	*out_string = (char *)prop;
	return 0;
}

#ifdef fdt_test
void of_testcase01(void)
{
	struct device_node* dev = of_find_compatible_node(NULL, NULL, "of_iomap,irq_of_parse_and_map");
	u32 start = 0;

	if(NULL == dev)
	{
		printk("of_find_compatible_node fail\n");
		return ;
	}

	start = (u32)of_iomap(dev, 0);
	if(0 == start)
	{
		printk("of_iomap fail\n");
		return ;
	}

	printk("start=0x%x\n", start);
}

void of_testcase02(void)
{
	struct device_node* dev = of_find_compatible_node(NULL, NULL, "of_iomap,irq_of_parse_and_map");
	u32 intno1, intno2;

	if(NULL == dev)
	{
		printk("of_find_compatible_node fail\n");
		return ;
	}

	intno1 = (u32)irq_of_parse_and_map(dev, 0);
	if(0 == intno1)
	{
		printk("of_iomap fail index0\n");
		return ;
	}

	intno2 = (u32)irq_of_parse_and_map(dev, 1);
	if(0 == intno2)
	{
		printk("of_iomap fail index1\n");
		return ;
	}

	printk("intno1=%d, intno2=%d\n", intno1, intno2);
}

void fdt_read_test(void)
{
	int len;
	int offset;
	const void *fdt = NULL;
	u32 *reg;

	/* step0: get dtb file address in memory */
	fdt = (const void *)DDR_MCORE_DTS_ADDR;

	/* step1: get node offset of ipc1 */
	offset = fdt_node_offset_by_compatible(fdt, -1, "of_iomap,irq_of_parse_and_map");
	if (offset < 0) 
	{
		printk("Could not find ipc1 node.\n");
		return ;
	}

	/* step2-1: get node value, reg cell has 1 cell, which has 2 items */
	reg = (u32 *)fdt_getprop(fdt, offset, "reg", &len);
	printk("reg=<0x%x, 0x%x>, len=0x%x\n", cpu_to_fdt32(*reg), cpu_to_fdt32(*(reg+1)), len);

	/* step2-2: get node value, interrupts cell has 2 cells, which has 3 items */
	reg = (u32 *)fdt_getprop(fdt, offset, "interrupts", &len);
	printk("interrupts=<0x%x, 0x%x>, len=0x%x\n", cpu_to_fdt32(*(reg+1)), cpu_to_fdt32(*(reg+4)), len);

}
#endif

