#include <osl_types.h>
#include <of.h>
#include "dts.h"
/*lint --e{712, 713, 737, 747, 578}*/

void of_print_level_set(u32 print_level)
{
	 (void)bsp_mod_level_set(BSP_MODU_OF, print_level);
}

/* device node节点属性dump */
int of_dn_dump(const char *str)
{
	struct device_node *np = NULL;

	if (NULL == str)
	{
		of_pr_err("usage: of_dn_dump node_compatible_name(char *)\n");
		return -1;
	}

	np = of_find_compatible_node(NULL, NULL, str);
	if(NULL == np)
	{
		of_pr_err("device node not exist\n");
		return -1;
	}

	of_pr_err("[full_name]%s, [name]%s, [type]0x%x, [properties]0x%p\n", np->full_name, np->name, np->type, np->properties);
	return 0; 
}

/* device node节点的properties信息dump */
int of_prop_dump(struct property *prop)
{
	if (NULL == prop)
	{
		of_pr_err("usage: of_prop_dump property(struct property *)\n");
		return -1;
	}

	of_pr_err("[name]%s, [length]0x%x, [value]0x%x, [next]0x%p\n", prop->name, prop->length, prop->value, prop->next);
	return 0;
}

/* device node节点的interrupts属性dump */
int of_int_dump(const char *str, u32 index)
{
	struct device_node *device = NULL;
	u32 intsize = 3; /* interrupt-cells 值取得 */
	const __be32 *intspec;
	u32 intlen = 0;
	u32 irq[3] = {0};
	u32 i = 0;

	if (NULL == str)
	{
		of_pr_err("usage: of_int_dump node_compatible_name(char *), cells_index(int)\n");
		return -1;
	}

	device = of_find_compatible_node(NULL, NULL, str);
	if(NULL == device)
	{
		of_pr_err("device node not exist\n");
		return -1;
	}
	of_pr_debug("%s, %s, %d\n", device->full_name, device->name, device->type);

	/* Get the interrupts property */
	intspec = of_get_property(device, "interrupts", (int *)&intlen);
	if (intspec == NULL)
	{
		of_pr_err("interrpts node value is null\n");
		return -1;
	}
	intlen /= sizeof(*intspec);

	of_pr_err(" intspec=%d intlen=%d, intsize=%d\n", be32_to_cpup(intspec), intlen, intsize);

	/* Check index */
	if ((index + 1) * intsize > intlen)
	{
		of_pr_err("index error\n");
		return -1;
	}

	intspec = intspec + index * intsize;

	/* Get new specifier and map it */
	for (i = 0; i < intsize; i++)
		irq[i] = of_read_number(intspec +i, 1);
	of_pr_err("irq[3]={%d, %d, %d}\n", irq[0], irq[1], irq[2]);
	return 0;
}

int of_reg_dump(const char *str, u32 index)
{
	struct device_node *device = NULL;
	const __be32 *spec = NULL;
	const __be32 *prop = NULL;
	int cells_size, len = 0;
	int na = 0, ns = 0;
	u64 start = 0, size = 0;

	if (NULL == str)
	{
		of_pr_err("usage: of_reg_dump node_compatible_name(char *), cells_index(int)\n");
		return -1;
	}

	device = of_find_compatible_node(NULL, NULL, str);
	if(!device)
	{
		of_pr_err("device node not exist\n");
		return -1;
	}
	of_pr_debug("%s, %s, %d\n", device->full_name, device->name, device->type);

	spec = of_get_property(device, "reg", (int *)&len);
	len /= 4;

	if (NULL == spec)
	{
		of_pr_err("cannot find reg property\n");
		return -1;
	}
	of_pr_debug("spec=0x%x, len=%d\n", spec, len);

	prop = of_get_property(device, "#address-cells", NULL);
	if(NULL != prop)
	{
		na = be32_to_cpup(prop);
		of_pr_debug("#address-cells=%d",  na);
	}
	prop = of_get_property(device, "#size-cells", NULL);
	if(NULL != prop)
	{
		ns = be32_to_cpup(prop);
		of_pr_debug("#size-cells=%d", ns);
	}

	cells_size = na + ns;
	if(cells_size == 0)
	{
		na = 1;
		ns = 1;
		cells_size = 2;
	}
	if((index * cells_size) >= (u32)len)
	{
		of_pr_err("index = %d is out of range\n", index);
		return -1;
	}

	start = of_read_number(spec + index *cells_size , 1);
	size  = of_read_number(spec + index *cells_size + na, ns);
	of_pr_err("reg = <0x%x 0x%x>\n", (u32)start, (u32)size);
	return 0;
}

